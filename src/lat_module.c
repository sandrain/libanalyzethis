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
#include "lat_iniconfig_sched.h"
#include "lat_device.h"
#include "lat_host_sched.h"

/* NOTE TO DEVELOPERS: do *not* use the C99 way to initialize a data structure,
   it *will* create some problems with some version of python. For example, the
   following creates a problem when loading the python module:
lat_module_t lat_module = {
    .lat_module_init                    = lat_iniconfig_platform_init,
    .lat_module_finalize                = lat_iniconfig_platform_fini,
    .lat_module_device_sched_init       = lat_device_sched_init_rr,
    .lat_module_device_sched_finalize   = lat_device_sched_fini_rr,
    .lat_module_device_sched_task       = lat_device_sched_task_rr,
    .lat_module_host_sched_init         = lat_host_sched_init_rr,
    .lat_module_host_sched_finalize     = lat_host_sched_fini_rr,
    .lat_module_host_sched_task         = lat_host_sched_task_rr,
    .lat_module_host_copy_file          = NULL,
    .lat_module_host_move_file          = NULL,
    .lat_module_meta_sched_init         = NULL,
    .lat_module_meta_sched_finalize     = NULL,
    .lat_module_meta_sched_task         = NULL,
    .lat_module_meta_sched_workflow     = lat_workflow_static_placement_noop,
    .verbose                            = false,
    .syscfg                             = NULL,
};
*/


lat_module_t lat_module;

int
lat_init_module ()
{
    lat_module.lat_module_init
        = lat_iniconfig_platform_init;
    lat_module.lat_module_finalize
        = lat_iniconfig_platform_fini;
    lat_module.lat_module_device_sched_init         = lat_device_sched_init_rr;
    lat_module.lat_module_device_sched_finalize     = lat_device_sched_fini_rr;
    lat_module.lat_module_device_sched_task         = lat_device_sched_task_rr;
    lat_module.lat_module_host_sched_init           = lat_host_sched_init_rr;
    lat_module.lat_module_host_sched_finalize       = lat_host_sched_fini;
    lat_module.lat_module_host_sched_task           = lat_host_sched_task_rr;
    lat_module.lat_module_host_sched_file           = NULL;
    lat_module.lat_module_host_copy_file            = NULL;
    lat_module.lat_module_host_move_file            = NULL;
    lat_module.lat_module_meta_sched_init           = lat_meta_sched_init_rr;
    lat_module.lat_module_meta_sched_finalize       = lat_meta_sched_fini;
    lat_module.lat_module_meta_sched_task           = lat_meta_sched_task_rr;
    lat_module.lat_module_meta_sched_file           = NULL;
    lat_module.lat_module_meta_sched_workflow
        = lat_workflow_static_placement_noop,
    lat_module.verbose                              = false;
    lat_module.syscfg                               = NULL;

    return LAT_SUCCESS;
}

