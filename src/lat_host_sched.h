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

#ifndef LAT_HOST_SCHED_H
#define LAT_HOST_SCHED_H

#include "lat_task.h"

int
lat_host_sched_init_rr (lat_host_t          *host,
                        lat_host_sched_t    **host_sched);

int
lat_host_sched_fini_rr (lat_host_sched_t    **host_sched);

int
lat_host_sched_task_rr (lat_host_sched_t    *host_sched,
                        lat_task_t          *task,
                        lat_device_t        **dev);

#endif /* LAT_HOST_SCHED_H */

