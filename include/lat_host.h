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

#ifndef LAT_HOST_H
#define LAT_HOST_H

#include "lat_dev.h"

typedef struct lat_host_t {
    ssize_t         num_afes;
    lat_device_t    *afes_cfg;
} lat_host_t;

#define ALLOC_HOST_T(h) do {            \
    h = malloc (sizeof (lat_host_t));   \
    if (h != NULL) {                    \
        h->num_afes = 0;                \
        h->afes_cfg = NULL;             \
    }                                   \
} while (0)

#define DISPLAY_HOST_T(h) do {                                              \
    if (h != NULL) {                                                        \
        fprintf (stdout, "Number of AFEs per server: %zd\n", h->num_afes);  \
        DISPLAY_DEVICE_T(h->afes_cfg);                                      \
    }                                                                       \
} while (0)

typedef void* lat_host_sched_t;

#endif /* LAT_HOST_H */
