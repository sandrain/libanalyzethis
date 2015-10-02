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

#ifndef LAT_CLUSTER_H
#define LAT_CLUSTER_H

#include "lat_host.h"

/*
 * Basic assumptions:
 * - all servers have the exact same configuration
 */
typedef struct lat_cluster_t {
    ssize_t     num_servers;    /* Number of servers */
    lat_host_t  *server_cfg;    /* Generic description of a server configuration */
} lat_cluster_t;

#define ALLOC_CLUSTER_T(c) do {                         \
    c = (lat_cluster_t*)malloc (sizeof(lat_cluster_t)); \
    if (c != NULL) {                                    \
        c->num_servers  = 0;                            \
        c->server_cfg   = NULL;                         \
    }                                                   \
} while (0)

#define DISPLAY_CLUSTER_T(c) do {                                       \
    if (c != NULL) {                                                    \
        fprintf (stdout, "Number of servers: %zd\n", c->num_servers);   \
        DISPLAY_HOST_T(c->server_cfg);                                  \
    }                                                                   \
} while (0)

#endif /* LAT_CLUSTER_H */
