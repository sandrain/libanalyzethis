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
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "lat_constants.h"
#include "lat_core.h"
#include "lat_dev.h"
#include "lat_task.h"
#include "lat_debug.h"
#include "lat_sched.h"

typedef struct lat_device_rr_sched_s {
    ssize_t     num_cores;
    lat_core_t  last_core;
} lat_device_rr_sched;

lat_device_rr_sched rr_dev_sched;

typedef struct lat_device_random_sched_s {
    ssize_t num_cores;
} lat_device_random_sched_t;

lat_device_random_sched_t random_dev_sched;


int
lat_device_sched_init_rr (lat_device_t          *dev,
                          lat_device_sched_t    **dev_sched)
{
    if (dev == NULL)
        return LAT_BAD_PARAM;

    rr_dev_sched.last_core  = dev->num_cores - 1; /* This will assign the first
                                                 task to the first core */
    rr_dev_sched.num_cores  = dev->num_cores;

    *dev_sched = (void*)&rr_dev_sched;

    return LAT_SUCCESS;
}

int
lat_device_sched_fini_rr (lat_device_sched_t **dev_sched)
{
    return LAT_SUCCESS;
}

int
lat_device_sched_task_rr (lat_device_sched_t    *dev_sched,
                          lat_task_t            *task,
                          lat_core_t            **core)
{
    if (dev_sched == NULL)
        LAT_FATAL (LAT_BAD_PARAM, ("Invalid device scheduler"));

    rr_dev_sched.last_core =
        (rr_dev_sched.last_core + 1) % rr_dev_sched.num_cores;
    if (lat_module.verbose == true)
        LAT_INFO (("Core id: %d", rr_dev_sched.last_core));

    *core = &rr_dev_sched.last_core;

    return LAT_SUCCESS;
}

int
lat_device_sched_init_random (lat_device_t          *dev,
                              lat_device_sched_t    **dev_sched)
{
    time_t t;

    if (dev == NULL)
        return LAT_BAD_PARAM;

    srand ((unsigned) time (&t));
    random_dev_sched.num_cores = dev->num_cores;

    *dev_sched = (void*)&random_dev_sched;

    return LAT_SUCCESS;
}

int
lat_device_sched_fini_random (lat_device_sched_t **dev_sched)
{
    return LAT_SUCCESS;
}

int
lat_device_sched_init_fini (lat_device_sched_t **dev_sched)
{
    if (dev_sched != NULL && *dev_sched != NULL)
    {
        free (*dev_sched);
        *dev_sched = NULL;
        return LAT_SUCCESS;
    } else {
        LAT_FATAL (LAT_ERROR, ("Invalid scheduler"));
    }
}

int
lat_device_sched_task_random (lat_device_sched_t    *dev_sched,
                              lat_task_t            *task,
                              lat_core_t            **core)
{
    lat_core_t                  core_id;
    lat_device_random_sched_t   *random_dev_sched;

    if (dev_sched == NULL)
        LAT_FATAL (LAT_BAD_PARAM, ("INvalid device scheduler"));

    random_dev_sched = (lat_device_random_sched_t*)dev_sched;

    core_id = (lat_core_t)(rand() % random_dev_sched->num_cores);

    *core = &core_id;

    return LAT_SUCCESS;
}
