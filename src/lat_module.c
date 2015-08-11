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

#include "lat_sched.h"
#include "lat_workflow.h"

lat_module_t lat_module = {
    .lat_module_device_sched_init       = NULL,
    .lat_module_device_sched_finalize   = NULL,
    .lat_module_device_sched_task       = NULL,
    .lat_module_host_sched_init         = NULL,
    .lat_module_host_sched_finalize     = NULL,
    .lat_module_host_sched_task         = NULL,
    .lat_module_host_copy_file          = NULL,
    .lat_module_host_move_file          = NULL,
    .lat_module_meta_sched_init         = NULL,
    .lat_module_meta_sched_finalize     = NULL,
    .lat_module_meta_sched_task         = NULL,
    .lat_module_meta_sched_workflow     = lat_workflow_static_placement_noop,
};