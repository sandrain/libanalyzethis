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

#ifndef LAT_DEVICE_H
#define LAT_DEVICE_H

#include "lat_task.h"

int
lat_device_sched_init_rr (lat_device_t          *dev,
                          lat_device_sched_t    **dev_sched);

int
lat_device_sched_fini_rr (lat_device_sched_t **dev_sched);

int
lat_device_sched_task_rr (lat_device_sched_t    *dev_sched,
                          lat_task_t            *task,
                          lat_core_t            **core);

int
lat_device_sched_init_random (lat_device_t          *dev,
                              lat_device_sched_t    **dev_sched);

int
lat_device_sched_fini_random (lat_device_sched_t **dev_sched);

int
lat_device_sched_task_random (lat_device_sched_t    *dev_sched,
                              lat_task_t            *task,
                              lat_core_t            **core);

#endif /* LAT_DEVICE_H */
