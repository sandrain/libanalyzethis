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
#include "lat_debug.h"
#include "lat_host.h"
#include "lat_task.h"
#include "lat_sched.h"
#include "lat_dev.h"

typedef struct task_sched_data_t {
    ssize_t last_assigned;
} task_sched_data_t;

typedef struct file_sched_data_t {
    ssize_t last_assigned;
} file_sched_data_t;

typedef struct lat_host_rr_sched_t {
    ssize_t num_afes;
    task_sched_data_t   task_sched_data;
    file_sched_data_t   file_sched_data;
} lat_host_rr_sched_t;

typedef struct lat_meta_rr_sched_t {
    ssize_t num_servers;
    task_sched_data_t   task_sched_data;
    file_sched_data_t   file_sched_data;
} lat_meta_rr_sched_t;

typedef struct lat_host_random_sched_t {
    ssize_t num_afes;
} lat_host_random_sched_t;

typedef struct lat_meta_random_sched_t {
    ssize_t num_servers;
    task_sched_data_t   task_sched_data;
    file_sched_data_t   file_sched_data;
} lat_meta_random_sched_t;

/*
 * Scheduling across multiple AFE on a single node.
 */

int
lat_host_sched_init_rr (lat_host_t          *host,
                        lat_host_sched_t    **host_sched)
{
    lat_host_rr_sched_t *rr_host_sched;

    if (host == NULL) {
        *host_sched = NULL;
        return LAT_BAD_PARAM;
    }

    rr_host_sched = malloc (sizeof (lat_host_rr_sched_t));
    if (rr_host_sched == NULL) {
        *host_sched = NULL;
        LAT_FATAL (LAT_ERROR, ("malloc() failed"));
    }

    /* This will assign the first task to the first afe */
    rr_host_sched->task_sched_data.last_assigned = host->num_afes - 1;
    rr_host_sched->file_sched_data.last_assigned = host->num_afes - 1;
    rr_host_sched->num_afes  = host->num_afes;

    *host_sched = (void*)rr_host_sched;

    return LAT_SUCCESS;
}

int
lat_host_sched_init_random (lat_host_t          *host,
                            lat_host_sched_t    **host_sched)
{
    time_t t;
    lat_host_random_sched_t *random_host_sched;

    if (host == NULL) {
        *host_sched = NULL;
        return LAT_BAD_PARAM;
    }

    random_host_sched = malloc (sizeof(lat_host_random_sched_t));
    if (random_host_sched == NULL) {
        *host_sched = NULL;
        LAT_FATAL (LAT_ERROR, ("malloc() failed"));
    }

    srand ((unsigned) time (&t));
    random_host_sched->num_afes = host->num_afes;

    *host_sched = (void*)random_host_sched;

    return LAT_SUCCESS;
}

int
lat_host_sched_fini (lat_host_sched_t **host_sched)
{
    if (host_sched != NULL && *host_sched != NULL) {
        free (*host_sched);
        *host_sched = NULL;
        return LAT_SUCCESS;
    } else {
        LAT_FATAL (LAT_ERROR, ("Invalid scheduler"));
    }
}

int
lat_host_sched_task_rr (lat_host_sched_t    *host_sched,
                        lat_task_t          *task,
                        lat_device_t        **dev)
{
    lat_device_t        *my_dev = NULL;
    lat_host_rr_sched_t *rr_host_sched;

    if (host_sched == NULL) {
        *dev = NULL;
        LAT_FATAL (LAT_BAD_PARAM, ("Invalid host scheduler"));
    }

    rr_host_sched = (lat_host_rr_sched_t*)host_sched;

    rr_host_sched->task_sched_data.last_assigned =
        (rr_host_sched->task_sched_data.last_assigned + 1) %
        rr_host_sched->num_afes;

    if (lat_module.verbose == true)
        LAT_INFO (("AFE/device id: %d",
                   rr_host_sched->task_sched_data.last_assigned));

    /* Create a new device structure to return the required info */
    ALLOC_DEVICE_T(my_dev);
    my_dev->dev_id = rr_host_sched->task_sched_data.last_assigned;
    
    *dev = my_dev;

    return LAT_SUCCESS;
}

int
lat_host_sched_task_random (lat_host_sched_t    *host_sched,
                            lat_task_t          *task,
                            lat_device_t        **dev)
{
    lat_device_t            *my_dev = NULL;
    lat_host_random_sched_t *random_host_sched;

    if (host_sched == NULL) {
        *dev = NULL;
        LAT_FATAL (LAT_BAD_PARAM, ("Invalid host scheduler"));
    }

    random_host_sched = (lat_host_random_sched_t*)host_sched;

    ALLOC_DEVICE_T(my_dev);
    my_dev->dev_id = rand() % random_host_sched->num_afes;

    *dev = my_dev;

    return LAT_SUCCESS;
}

int
lat_host_sched_file_rr (lat_host_sched_t    *host_sched,
                        lat_file_t          *file,
                        lat_device_t        **dev)
{
    lat_device_t        *my_dev = NULL;
    lat_host_rr_sched_t *rr_host_sched;

    if (host_sched == NULL) {
        *dev = NULL;
        LAT_FATAL (LAT_BAD_PARAM, ("Invalid host scheduler"));
    }

    rr_host_sched = (lat_host_rr_sched_t*)host_sched;

    rr_host_sched->file_sched_data.last_assigned =
        (rr_host_sched->file_sched_data.last_assigned + 1) %
        rr_host_sched->num_afes;

    if (lat_module.verbose == true)
        LAT_INFO (("AFE/device id: %d",
                   rr_host_sched->file_sched_data.last_assigned));

    /* Create a new device structure to return the required info */
    ALLOC_DEVICE_T(my_dev);
    my_dev->dev_id = rr_host_sched->file_sched_data.last_assigned;

    *dev = my_dev;

    return LAT_SUCCESS;
}

int
lat_host_sched_file_random (lat_host_sched_t    *host_sched,
                            lat_file_t          *file,
                            lat_device_t        **dev)
{
    lat_device_t            *my_dev = NULL;
    lat_host_random_sched_t *random_host_sched;

    if (host_sched == NULL) {
        *dev = NULL;
        LAT_FATAL (LAT_BAD_PARAM, ("Invalid host scheduler"));
    }

    random_host_sched = (lat_host_random_sched_t*)host_sched;
    
    ALLOC_DEVICE_T(my_dev);
    my_dev->dev_id = rand() % random_host_sched->num_afes;

    *dev = my_dev;

    return LAT_SUCCESS;
}

/*
 * Scheduling across multiple hosts.
 */

int
lat_meta_sched_init_rr (lat_cluster_t    *cluster,
                        lat_meta_sched_t **meta_sched)
{
    lat_meta_rr_sched_t *rr_meta_sched;

    if (cluster == NULL) {
        *meta_sched = NULL;
        return LAT_BAD_PARAM;
    }

    rr_meta_sched = malloc (sizeof (lat_meta_rr_sched_t));
    if (rr_meta_sched == NULL) {
        *meta_sched = NULL;
        LAT_FATAL (LAT_ERROR, ("malloc() failed"));
    }

    /* This will assign the first task to the first host */
    rr_meta_sched->task_sched_data.last_assigned = cluster->num_servers - 1;
    rr_meta_sched->file_sched_data.last_assigned = cluster->num_servers - 1;
    rr_meta_sched->num_servers                   = cluster->num_servers;

    *meta_sched = (void*)&rr_meta_sched;

    return LAT_SUCCESS;
}

int
lat_meta_sched_init_random (lat_cluster_t       *cluster,
                            lat_meta_sched_t    **meta_sched)
{
    time_t                  t;
    lat_meta_random_sched_t *random_meta_sched;

    if (cluster == NULL) {
        *meta_sched = NULL;
        return LAT_BAD_PARAM;
    }

    random_meta_sched = malloc (sizeof (lat_meta_random_sched_t));
    if (random_meta_sched == NULL) {
        *meta_sched = NULL;
        LAT_FATAL (LAT_ERROR, ("malloc() failed"));
    }

    srand ((unsigned) time (&t));
    random_meta_sched->num_servers = cluster->num_servers;

    *meta_sched = (void*)random_meta_sched;

    return LAT_SUCCESS;
}

int
lat_meta_sched_fini (lat_meta_sched_t **meta_sched)
{
    if (meta_sched != NULL && *meta_sched != NULL) {
        free (*meta_sched);
        *meta_sched = NULL;
        return LAT_SUCCESS;
    } else {
        return LAT_ERROR;
    }
}

int
lat_meta_sched_task_rr (lat_meta_sched_t    *meta_sched,
                        lat_task_t          *task,
                        lat_host_t          **host)
{
    lat_host_t          *my_host = NULL;
    lat_meta_rr_sched_t *rr_meta_sched;

    if (meta_sched == NULL)
        LAT_FATAL (LAT_BAD_PARAM, ("Invalid meta scheduler"));

    rr_meta_sched = (lat_meta_rr_sched_t*)meta_sched;
    rr_meta_sched->task_sched_data.last_assigned =
        (rr_meta_sched->task_sched_data.last_assigned + 1) %
        rr_meta_sched->num_servers;

    if (lat_module.verbose == true)
        LAT_INFO (("Host id: %d",
                   rr_meta_sched->task_sched_data.last_assigned));

    /* Create a new host structure to return the required info */
    ALLOC_HOST_T(my_host);
    my_host->host_id = rr_meta_sched->task_sched_data.last_assigned;

    *host = my_host;

    return LAT_SUCCESS;
}

int
lat_meta_sched_file_rr (lat_meta_sched_t    *meta_sched,
                        lat_file_t          *file,
                        lat_host_t          **host)
{
    lat_host_t          *my_host = NULL;
    lat_meta_rr_sched_t *rr_meta_sched;

    if (meta_sched == NULL)
        LAT_FATAL (LAT_BAD_PARAM, ("Invalid meta scheduler"));

    rr_meta_sched = (lat_meta_rr_sched_t*)meta_sched;
    rr_meta_sched->file_sched_data.last_assigned =
        (rr_meta_sched->file_sched_data.last_assigned + 1) %
        rr_meta_sched->num_servers;

    if (lat_module.verbose == true)
        LAT_INFO (("Host id: %d",
                   rr_meta_sched->file_sched_data.last_assigned));

    /* Create a new host structure to return the required info */
    ALLOC_HOST_T(my_host);
    my_host->host_id = rr_meta_sched->file_sched_data.last_assigned;

    *host = my_host;

    return LAT_SUCCESS;
}

int
lat_meta_sched_file_random (lat_meta_sched_t    *meta_sched,
                            lat_file_t          *file,
                            lat_host_t          **host)
{
    lat_host_t              *my_host = NULL;
    lat_meta_random_sched_t *random_meta_sched;

    if (meta_sched == NULL)
        LAT_FATAL (LAT_BAD_PARAM, ("Invalid meta scheduler"));

    random_meta_sched = (lat_meta_random_sched_t*)meta_sched;

    /* Create a new host structure to return the required info */
    ALLOC_HOST_T(my_host);
    my_host->host_id = rand() % random_meta_sched->num_servers;

    *host = my_host;

    return LAT_SUCCESS;
}
