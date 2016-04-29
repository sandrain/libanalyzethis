/* vim: set softtabstop=4:shiftwidth=4:expandtab */

/*
 * Copyright (c) 2015       UT-Battelle, LLC
 *                          All rights reserved.
 *
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 *
 */

#include <string.h>

#include "lat_debug.h"
#include "lat_inifile_parser.h"
#include "lat_iniconfig_sched.h"
#include "lat_sched.h"

static int
iniconfig_find_block (char *name, lat_iniconfig_t *cfg, lat_ini_block_t **block)
{
    int             i;
    lat_ini_block_t *b;

    for (i = 0; i < cfg->num_blocks; i++) {
        b = cfg->blocks[i];
        if (strcmp (b->name, name) == 0) {
            *block = b;
            return LAT_SUCCESS;
        }
    }

    *block = NULL;
    return LAT_ERROR;
}

static int
iniconfig_find_kv (char *key, lat_ini_block_t *block, char **value)
{
    int             i;
    lat_ini_kv_t    *kv;

    for (i = 0; i < block->num_keyvalue_pairs; i++) {
        kv = block->keyvalue_pairs[i];
        if (strcmp (kv->key, key) == 0) {
            *value = kv->value;
            return LAT_SUCCESS;
        }
    }

    *value = NULL;
    return LAT_ERROR;
}

int
lat_iniconfig_to_syscfg (lat_iniconfig_t *cfg, lat_cluster_t **syscfg)
{
    int             rc;
    lat_cluster_t   *s;
    char            *val_str;
    lat_ini_block_t *block;
    lat_host_t      *server_cfg;
    lat_device_t    *afe_cfg;
    char            *block_name;
    char            *key_name;

    s = *syscfg;
    if (s != NULL)
        LAT_FATAL (LAT_ERROR, ("System configuration is already set"));

    ALLOC_CLUSTER_T(s);
    if (s == NULL)
        LAT_FATAL (LAT_ERROR, ("ALLOC_CLUSTER_T() failed"));

    block_name  = "SERVERS";
    key_name    = "number_hosts";
    rc = iniconfig_find_block (block_name, cfg, &block);
    if (rc != LAT_SUCCESS)
        LAT_FATAL (LAT_ERROR, ("iniconfig_find_block() failed"));

    rc = iniconfig_find_kv (key_name, block, &val_str);
    if (rc != LAT_SUCCESS)
        LAT_FATAL (LAT_ERROR,
                   ("iniconfig_find_kv() failed (block: %s, key: %s)",
                    block_name, key_name));
    s->num_servers = (ssize_t)atoi (val_str);

    ALLOC_HOST_T (server_cfg);
    if (server_cfg == NULL)
        LAT_FATAL (LAT_ERROR, ("ALLOC_HOST_T() failed"));

    key_name = "number_afes";
    rc = iniconfig_find_kv (key_name, block, &val_str);
    if (rc != LAT_SUCCESS)
        LAT_FATAL (LAT_ERROR,
                   ("iniconfig_find_kv() failed (block: %s, key: %s)",
                    block_name, key_name));
    server_cfg->num_afes = (ssize_t)atoi (val_str);
    s->server_cfg = server_cfg;

    ALLOC_DEVICE_T (afe_cfg);
    if (afe_cfg == NULL)
        LAT_FATAL (LAT_ERROR, ("ALLOC_DEVICE_T() failed"));
    server_cfg->afes_cfg = afe_cfg;

    block_name = "AFE";
    rc = iniconfig_find_block ("AFE", cfg, &block);
    if (rc != LAT_SUCCESS)
        LAT_FATAL (LAT_ERROR,
                   ("iniconfig_find_block() failed (block:%s)",
                    block));

    key_name = "cores_per_afe";
    rc = iniconfig_find_kv (key_name, block, &val_str);
    if (rc != LAT_SUCCESS)
        LAT_FATAL (LAT_ERROR,
                   ("iniconfig_find_kv() failed (block: %s, key: %s)",
                    block_name, key_name));
    afe_cfg->num_cores = (ssize_t)atoi (val_str);

    *syscfg = s;

    return LAT_SUCCESS;
}

int
lat_iniconfig_platform_init (int argc, char **argv)
{
    int             i;
    char            *config_file = NULL;
    int             rc;
    lat_iniconfig_t *cfg;

    /* We parse the arguments. */
    for (i = 0; i < argc; i++) {
        if (argv[i] != NULL) {
            if (strcmp (argv[i], "verbose") == 0) {
                if (strcmp (argv[i+1], "1") == 0) {
                    fprintf (stdout, "Enabling verbosity...\n");
                    lat_module.verbose = true;
                    i++;
                }
            }

            if (strcmp (argv[i], "ini_config_file") == 0) {
                config_file = argv[i+1];
                i++;
            }
        }
    }

    /* We parse the configuration file to create a representation of the
       virtual platform. */
    if (config_file == NULL)
        return LAT_ERROR;

    if (lat_module.verbose == true)
        LAT_INFO (("Parsing configuration file %s", config_file));

    rc = lat_parse_inifile (config_file, &cfg);
    if (rc != LAT_SUCCESS)
        LAT_FATAL (LAT_ERROR, ("lat_parse_inifile() failed"));

    if (lat_module.verbose == true)
        lat_display_iniconfig (cfg);

    rc = lat_iniconfig_to_syscfg (cfg, &(lat_module.syscfg));
    if (rc != LAT_SUCCESS)
        LAT_FATAL (LAT_ERROR, ("lat_iniconfig_to_syscfg() failed"));

    if (lat_module.verbose == true) {
        DISPLAY_CLUSTER_T (lat_module.syscfg);
    }

    return LAT_SUCCESS;
}

int
lat_iniconfig_platform_fini ()
{
    return LAT_SUCCESS;
}
