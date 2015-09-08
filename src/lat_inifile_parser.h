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

#ifndef __LAT_INICONFIG_PARSER_H
#define __LAT_INICONFIG_PARSER_H

#include <sys/types.h>

typedef struct lat_ini_kv {
    char *key;
    char *value;
} lat_ini_kv_t;

typedef struct lat_ini_blocks {
    char            *name;
    ssize_t         num_keyvalue_pairs;
    lat_ini_kv_t    **keyvalue_pairs;
} lat_ini_block_t;

typedef struct lat_iniconfig {
    ssize_t             num_blocks;
    lat_ini_block_t     **blocks;
} lat_iniconfig_t;

int
lat_parse_inifile (char *inifile, lat_iniconfig_t **config);

void
lat_display_iniconfig (lat_iniconfig_t *cfg);

#define ALLOC_INICONFIG(config) do {                \
    config = malloc (sizeof (lat_iniconfig_t));     \
    if (config != NULL) {                           \
        config->num_blocks  = 0;                    \
        config->blocks      = NULL;                 \
    }                                               \
} while (0)

#define ALLOC_INICONFIG_BLOCK(block) do {                                   \
    block                           = malloc (sizeof (lat_ini_block_t));    \
    if (block != NULL) {                                                    \
        block->name                 = NULL;                                 \
        block->num_keyvalue_pairs   = 0;                                    \
        block->keyvalue_pairs       = NULL;                                 \
    }                                                                       \
} while (0)

#define ALLOC_INICONFIG_KEYVAL(kv) do {         \
    kv = malloc (sizeof (lat_ini_kv_t));        \
    if (kv != NULL) {                           \
        kv->key = NULL;                         \
        kv->value = NULL;                       \
    }                                           \
} while (0)

#define ADD_BLOCK_TO_INICONFIG(config,block) do {                                   \
    if (config->num_blocks == 0) {                                                  \
        config->blocks      = malloc (sizeof(lat_ini_block_t*));                    \
        if (config->blocks != NULL) {                                               \
            config->blocks[0]   = block;                                            \
            config->num_blocks  = 1;                                                \
        }                                                                           \
    } else {                                                                        \
        config->num_blocks++;                                                       \
        config->blocks  = realloc (config->blocks,                                  \
                                   config->num_blocks * sizeof(lat_ini_block_t*));  \
        config->blocks[config->num_blocks - 1] = block;                             \
    }                                                                               \
} while (0)

#define ADD_KEYVAL_TO_BLOCK(block,keyval) do {                                  \
    if (block->num_keyvalue_pairs == 0) {                                       \
        block->keyvalue_pairs = malloc (sizeof (lat_ini_kv_t*));                \
        if (block->keyvalue_pairs != NULL) {                                    \
            block->num_keyvalue_pairs = 1;                                      \
            block->keyvalue_pairs[0] = keyval;                                  \
        }                                                                       \
    } else {                                                                    \
        block->num_keyvalue_pairs++;                                            \
        block->keyvalue_pairs                                                   \
            = realloc (block->keyvalue_pairs,                                   \
                       block->num_keyvalue_pairs * sizeof (lat_ini_kv_t*));     \
        if (block->keyvalue_pairs != NULL) {                                    \
            block->keyvalue_pairs[block->num_keyvalue_pairs - 1] = keyval;      \
        }                                                                       \
    }                                                                           \
} while (0)

#endif /* __LAT_INICONFIG_PARSER_H */
