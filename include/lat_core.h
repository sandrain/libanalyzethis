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

#ifndef LAT_CORE_H
#define LAT_CORE_H

/* Opaque handle to refer to a core on a specific AFE. For now, we represent
   a core via a unique ID (integer) */
typedef ssize_t lat_core_t;

#define LAT_DEV_NEXT_CORE(c) do {   \
    c + 1                           \
} while (0)

#endif /* LAT_CORE_H */
