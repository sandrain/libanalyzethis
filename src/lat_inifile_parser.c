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

#include <sys/types.h>
#include <stdio.h>

#include <string.h>

#include "lat_constants.h"
#include "lat_debug.h"
#include "lat_inifile_parser.h"

void lat_display_inikeyval (lat_ini_kv_t *kv);
void lat_display_iniblock (lat_ini_block_t *block);

/* XXX Clean memory upon error */
int
lat_parse_inifile (char *inifile, lat_iniconfig_t **config)
{
    FILE                *f;
    ssize_t             read;
    size_t              len         = 0;
    char                *line       = NULL;
    int                 pos         = 0;
    int                 equal_pos   = 0;
    int                 key_end;
    int                 value_end;
    int                 line_number = 0;
    lat_iniconfig_t     *iniconfig  = NULL;
    lat_ini_block_t     *cur_block  = NULL;

    f = fopen (inifile, "r");
    if (f == NULL)
        LAT_FATAL (LAT_ERROR, ("fopen() failed"));

    ALLOC_INICONFIG(iniconfig);
    if (iniconfig == NULL)
        LAT_FATAL (LAT_ERROR, ("INIT_INICONFIG_STRUCT() failed"));
    *config = iniconfig;

    while ((read = getline (&line, &len, f)) != -1) {
        char *key;
        char *value;

        line_number ++;
        pos = 0;

        /* Skip all white spaces at the begining of the line */
        while (line[pos] == ' ') {
            pos ++;
        }

        /* If the line is a comment, we skip the line */
        if (line[pos] == '#')
            continue;

        /* We skip empty lines */
        if (pos == strlen (line) || line[pos] == '\n')
            continue;

        /* We check whether it is the begining of a block */
        if (line[pos] == '[') {
            int             j;
            lat_ini_block_t *new_block;

            /* If so we extract the name of the block */
            int     end         = pos;
            char    *block_name;

            /* We search for the end of the block name */
            while (line[end] != ']' && pos < strlen (line)) {
                end ++;
            }

            if (line[end] != ']') {
                LAT_ERR_MSG (("Invalid block name"));
                goto exit;
            }

            /* Now we extract the name of the block */
            pos++; /* We do not want the '[' character */
            block_name = malloc ((end - pos + 1) * sizeof (char));
            if (block_name == NULL) {
                LAT_ERR_MSG (("malloc() failed"));
                goto exit;
            }

            for (j = 0; j < end - pos; j++) {
                block_name[j] = line[pos + j];
            }
            block_name[end - pos] = '\0';

            ALLOC_INICONFIG_BLOCK (new_block);
            if (new_block == NULL)
                LAT_FATAL (LAT_ERROR, ("ALLOC_INICONFIG_BLOCK() failed"));
            new_block->name = block_name;
            cur_block = new_block;

            ADD_BLOCK_TO_INICONFIG (iniconfig, new_block);
        } else {
            int             j;
            lat_ini_kv_t    *new_keyval;

            /* XXX: the code does not work if spaces or tabs are present before the key */

            /* If we end up here, we have a key/value pair */
            equal_pos = pos;
            while (line[equal_pos] != '=' && equal_pos < strlen (line)) {
                equal_pos ++;
            }

            if (line[equal_pos] != '=') {
                LAT_ERR_MSG (("Invalid key/value pair (line #: %d, %s)",
                              line_number, line));
                goto exit;
            }

            /* For the key, we need to find the last character before '=',
               excluding spaces */
            key_end = pos;
            while (line[key_end] != ' ' && key_end != equal_pos) {
                key_end++;
            }

            key = malloc ((key_end - pos + 1) * sizeof (char));
            if (key == NULL) {
                LAT_ERR_MSG (("malloc() failed"));
                goto exit;
            }

            for (j = 0; j < key_end - pos; j++) {
                key[j] = line[pos + j];
            }
            key[key_end - pos] = '\0';

            /* Now we get the value */
            value_end = equal_pos;

            /* skip the spaces before the value */
            value_end++; /* We skip the '=' character */
            while (line[value_end] == ' ')
                value_end++;

            /* Find the actual end of the value, ignoring spaces */
            while (line[value_end] != ' ' && line[value_end] != '\n') {
                value_end++;
            }

            while (line[equal_pos] == '=' || line[equal_pos] == ' ') {
                equal_pos ++;
            }
            value = malloc ((value_end - equal_pos + 1) * sizeof (char));
            if (value == NULL) {
                LAT_ERR_MSG (("malloc() failed"));
                goto exit;
            }

            for (j = 0; j < value_end - equal_pos; j++) {
                value[j] = line[equal_pos + j];
            }
            value[value_end - equal_pos] = '\0';

            ALLOC_INICONFIG_KEYVAL (new_keyval);
            if (new_keyval == NULL) {
                LAT_FATAL (LAT_ERROR, ("ALLOC_INICONFIG_KEYVAL() failed"));
            }
            new_keyval->key     = key;
            new_keyval->value   = value;
            ADD_KEYVAL_TO_BLOCK (cur_block, new_keyval);
        }
    }

 exit:
    fclose (f);

    return LAT_SUCCESS;
}

void lat_display_inikeyval (lat_ini_kv_t *kv)
{
    fprintf (stdout, "K/V: %s/%s\n", kv->key, kv->value);
}

void
lat_display_iniblock (lat_ini_block_t *block)
{
    int i;

    fprintf (stdout, "Block name: %s - Number of key/value pairs: %zd\n",
             block->name, block->num_keyvalue_pairs);
    for (i = 0; i < block->num_keyvalue_pairs; i++) {
        lat_display_inikeyval (block->keyvalue_pairs[i]);
    }
}

void
lat_display_iniconfig (lat_iniconfig_t *cfg)
{
    int i;

    fprintf (stdout, "Number of blocks: %zd\n", cfg->num_blocks);
    for (i = 0; i < cfg->num_blocks; i++) {
        lat_display_iniblock (cfg->blocks[i]);
    }
}
