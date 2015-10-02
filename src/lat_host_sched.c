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

#include "lat_constants.h"
#include "lat_debug.h"
#include "lat_host.h"
#include "lat_task.h"
#include "lat_sched.h"
#include "lat_dev.h"

typedef struct lat_host_rr_sched {
    ssize_t num_afes;
    ssize_t last_afe_id;
} lat_host_rr_sched;

lat_host_rr_sched rr_host_sched;

int
lat_host_sched_init_rr (lat_host_t          *host,
                        lat_host_sched_t    **host_sched)
{
    if (host == NULL)
        return LAT_BAD_PARAM;

    rr_host_sched.last_afe_id  = host->num_afes - 1; /* This will assign the
                                                        first task to the
                                                        first afe */
    rr_host_sched.num_afes  = host->num_afes;

    *host_sched = (void*)&rr_host_sched;

    return LAT_SUCCESS;
}

int
lat_host_sched_fini_rr (lat_host_sched_t    **host_sched)
{
    return LAT_SUCCESS;
}

int
lat_host_sched_task_rr (lat_host_sched_t    *host_sched,
                        lat_task_t          *task,
                        lat_device_t        **dev)
{
    lat_device_t    *my_dev = NULL;

    if (host_sched == NULL)
        LAT_FATAL (LAT_BAD_PARAM, ("Invalid host scheduler"));

    rr_host_sched.last_afe_id =
        (rr_host_sched.last_afe_id + 1) % rr_host_sched.num_afes;

    if (lat_module.verbose == true)
        LAT_INFO (("AFE/device id: %d", rr_host_sched.last_afe_id));

    /* Create a new device structure to return the required info */
    ALLOC_DEVICE_T(my_dev);
    my_dev->dev_id = rr_host_sched.last_afe_id;
    
    *dev = my_dev;

    return LAT_SUCCESS;
}

