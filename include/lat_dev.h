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

#ifndef LAT_DEV_H
#define LAT_DEV_H

typedef struct lat_device_t {
    ssize_t num_cores;
} lat_device_t;

typedef void* lat_device_sched_t;

#define ALLOC_DEVICE_T(d) do {          \
    d = malloc (sizeof (lat_device_t)); \
    if (d != NULL) {                    \
        d->num_cores = 0;               \
    }                                   \
} while (0)

#define DISPLAY_DEVICE_T(d) do {                                            \
    if (d != NULL) {                                                        \
        fprintf (stdout, "Number of cores per AFE: %zd\n", d->num_cores);   \
    }                                                                       \
} while (0)

#define LAT_DEVICE_NUM_CORES(dev) do {  \
    dev->num_cores                      \
} while (0)

#endif /* LAT_DEV_H */
