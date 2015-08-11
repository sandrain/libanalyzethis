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


#ifndef LAT_SCHED_H
#define LAT_SCHED_H

#include <stdio.h>

#include "lat_cluster.h"
#include "lat_core.h"
#include "lat_dev.h"
#include "lat_file.h"
#include "lat_host.h"
#include "lat_metasched.h"
#include "lat_task.h"

/*
 * AFE-device level scheduling.
 *
 * Define the scheduling functions used at a device level.
 * At the device level, we handle multiple core are available.
 * The core of the scheduling algorithm
 * is therefore to assign tasks to a specific core. Files are
 * assumed to be present, higher level scheduler are supposed
 * to ensure they are.
 */

/**
 * Initialize a device-level scheduler.
 *
 * @param[in]   dev Structure representing the device. It includes the
 *                  number of cores and potentially a description of the
 *                  core in the context of heterogeneous devices.
 * @param[out]  dev_sched   Structure representing the initialized
 *                          device-level scheduler.
 * @return  LAT_SUCCESS     The device-level scheduler was successfully
 *                          initialized.
 * @return  LAT_ERROR       A fatal error occured during the initialization of
 *                          the device-level scheduler.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
typedef int
(*lat_device_sched_init_fn_t) (lat_device_t          *dev,
                               lat_device_sched_t    **dev_sched);

/**
 * Finalize a device-level scheduler.
 *
 * @param[in/out]   dev_sched  Structure representing the device-level scheduler
 *                             to finalize. Upon successful finalization, the
 *                             pointer is set to NULL.
 * @return  LAT_SUCCESS     The device-level scheduler was successfully
 *                          finalized.
 * @return  LAT_ERROR       A fatal error occured during the finalization of
 *                          the device-level scheduler.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
typedef int
(*lat_device_sched_finalize_fn_t) (lat_device_sched_t **dev_sched);

/**
 * Schedule a task using a given device-level scheduler. The scheduler will
 * identify the target core for the execution of the task; it will not
 * actually schedule the task for execution on the core, the caller is in
 * charge of actually assigning the task to the core.
 *
 * @param[in]   dev_sched   Structure representing the device-level scheduler to
 *                          use for scheduling the task.
 * @param[in]   task        Structure representing the task to be scheduler.
 * @param[out]  core        Core selected by the scheduler. If no core has 
 *                          been selected, core is set to NULL.
 * @return  LAT_SUCCESS     The task was successfully scheduled.
 * @return  LAT_ERROR       A fatal error occured during the scheduling of the
 *                          task.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
typedef int
(*lat_device_sched_task_fn_t) (lat_device_sched_t    *dev_sched,
                               lat_task_t            *task,
                               lat_core_t            **core);

/*
 * Host-level scheduling.
 *
 * Define the scheduling functions used at the host level. At the
 * host level, multiple AFEs may be available. The core of the
 * scheduling algorithm is therefore to assign tasks to a specific
 * AFE and potentially copy/move the required files.
 */

/**
 * Initialize a host-level scheduler.
 *
 * @param[in]   host    Structure representing the host. It includes the
 *                      number of AFE devices and potentially a description
 *                      of the individual AFEs in the context of heterogeneous
 *                      hosts. It also potentially include a description of
 *                      the meta-scheduler(s) used on the platform.
 * @param[out] host_sched   Structure representing the initialized host-level
 *                          scheduler.
 * @return  LAT_SUCCESS     The host-level scheduler was successfully
 *                          initialized.
 * @return  LAT_ERROR       A fatal error occured during the initialization of
 *                          the host-level scheduler.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */ 
typedef int
(*lat_host_sched_init_fn_t) (lat_host_t          *host,
                             lat_host_sched_t    **host_sched);

/**
 * Finalize a host-level scheduler.
 *
 * @param[in/out]   host_sched  Structure representing the host-level scheduler
 *                              to finalize. Upon successful finalization, the
 *                              pointer is set to NULL.
 * @return  LAT_SUCCESS     The host-level scheduler was successfully finalized.
 * @return  LAT_ERROR       A fatal error occured during the finalization of
 *                          the host-level scheduler.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
typedef int
(*lat_host_sched_finalize_fn_t) (lat_host_sched_t **host_sched);

/**
 * Schedule a task using a given host-level scheduler. The scheduler will
 * identified the target core for the execution of the task; it will not
 * actually schedule the task for execution on the core, the caller is in
 * charge of actually assigning the task to the core.
 *
 * @param[in]   host_sched  Structure representing the host-level scheduler to
 *                          use for scheduling the task.
 * @param[in]   task        Structure representing the task to be scheduler.
 * @param[out]  dev         Device selected by the scheduler. If no device has 
 *                          been selected, device is set to NULL.
 * @return  LAT_SUCCESS     The task was successfully scheduled.
 * @return  LAT_ERROR       A fatal error occured during the scheduling of the
 *                          task.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
typedef int
(*lat_host_sched_task_fn_t) (lat_host_sched_t    **host_sched,
                             lat_task_t          *task,
                             lat_device_t        **dev);

/**
 * Copy a file from one host to another. This is a blocking function, the
 * file is guaranteed to be copied upon completion of the function.
 *
 * @param[in]   file        File to be copied.
 * @param[in]   src_host    Location (host) of the file to copy.
 * @param[in]   dest_host   Destination (host) for the file to be copied.
 * @return  LAT_SUCCESS     The file was successfully copied.
 * @return  LAT_ERROR       A fatal error occured during the copy.
 *                          We guarantee that no partial copy of the file is
 *                          left on the remote host.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
/*
 * XXX: does the scheduler really need to have this things? This library is
 * fairly agnostic from the underlying implementation so i would assume that
 * the caller code will be in charge of copying the files is required. But then
 * the question is really about how the caller can gather enough info about
 * file location and task scheduling to orchestrate file copies.
 */
typedef int
(*lat_host_copy_file_fn_t) (lat_file_t   *file,
                            lat_host_t   *src_host,
                            lat_host_t   *dest_host);

/**
 * Copy a file from one host to another. This is a blocking function, the
 * file is guaranteed to be moved upon completion of the function, i.e., the
 * file is guarenteed to be deleted from the source.
 *
 * @param[in]   file        File to be moved.
 * @param[in]   src_host    Location (host) of the file to move.
 * @param[in]   dest_host   Destination (host) for the file to be moved.
 * @return  LAT_SUCCESS     The file was successfully moved.
 * @return  LAT_ERROR       A fatal error occured during the transfer. The
 *                          source file is then guaranteed to still exist and
 *                          we guarantee that no partial copy remain on the
 *                          destination host.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
/*
 * XXX: does the scheduler really need to have this things? This library is
 * fairly agnostic from the underlying implementation so i would assume that
 * the caller code will be in charge of moving the files is required. But then
 * the question is really about how the caller can gather enough info about
 * file location and task scheduling to orchestrate file transfers.
 */
typedef int
(*lat_host_move_file_fn_t) (lat_file_t   *file,
                            lat_host_t   *src_host,
                            lat_host_t   *dest_host);

/*
 * Meta-scheduler.
 *
 * Define the scheduling functions used between hosts. At the
 * meta-scheduler level, multiple hosts are available. The core of
 * the scheduling algorithm is therefore to assign tasks to a
 * specific host and potentially copy/move the required files to/from
 * hosts.
 */

/**
 * Initialize a meta-scheduler.
 *
 * @param[in]   platform    Structure representing the platform. It includes the
 *                          number of hosts and potentially a description of the
 *                          individual hosts in the context of heterogeneous
 *                          devices.
 * @param[out]  meta_sched  Structure representing the initialized
 *                          meta-scheduler.
 * @return  LAT_SUCCESS     The meta-scheduler was successfully initialized.
 * @return  LAT_ERROR       A fatal error occured during the initialization of
 *                          the meta-scheduler.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
typedef int
(*lat_meta_sched_init_fn_t) (lat_cluster_t       *platform,
                             lat_meta_sched_t    **meta_sched);

/**
 * Finalize a meta-scheduler.
 *
 * @param[in/out]   meta_sched  Structure representing the meta-scheduler to
 *                              finalize. Upon successful finalization, the
 *                              pointer is set to NULL.
 * @return  LAT_SUCCESS     The meta-scheduler was successfully finalized.
 * @return  LAT_ERROR       A fatal error occured during the finalization of
 *                          the meta-scheduler.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
typedef int
(*lat_meta_sched_finalize_fn_t) (lat_meta_sched_t **meta_sched);

/**
 * Schedule a task using a given meta-scheduler. The scheduler will
 * identified the target host for the execution of the task; it will not
 * actually schedule the task for execution on the host, the caller is in
 * charge of actually assigning the task to the host.
 *
 * @param[in]   meta_sched  Structure representing the meta-scheduler to
 *                          use for scheduling the task.
 * @param[in]   task        Structure representing the task to be scheduler.
 * @param[out]  host        Host selected by the scheduler. If no host has 
 *                          been selected, host is set to NULL.
 * @return  LAT_SUCCESS     The task was successfully scheduled.
 * @return  LAT_ERROR       A fatal error occured during the scheduling of the
 *                          task.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
typedef int
(*lat_meta_sched_task_fn_t) (lat_meta_sched_t    *meta_sched,
                             lat_task_t          *task,
                             lat_host_t          **host);

/**
 * Schedule a workflow using a offline, static policy. For that, a file
 * representing the workflow is passed in and the resulting workflow (with
 * some task placement) is saved to a file for which a pointer is returned.
 *
 * @param[in]   f_in    XML file representing the workflow to schedule.
 * @param[out]  f_out   Pointer to XML file representing the workflow with
 *                      placed tasks.
 * @return  LAT_SUCCESS     The workflow was successfully (but maybe partially)
 *                          scheduled.
 * @return  LAT_ERROR       A fatal error occured during the scheduling of the
 *                          workflow.
 * @return  LAT_BAD_PARAM   One or more of the parameters is invalid.
 */
typedef int
(*lat_meta_sched_workflow_fn_t) (FILE    *f_in,
                                 FILE    **f_out);

/**
 * Basic structure of a module.
 */
struct lat_module_t {
    lat_device_sched_init_fn_t      lat_module_device_sched_init;
    lat_device_sched_finalize_fn_t  lat_module_device_sched_finalize;
    lat_device_sched_task_fn_t      lat_module_device_sched_task;
    lat_host_sched_init_fn_t        lat_module_host_sched_init;
    lat_host_sched_finalize_fn_t    lat_module_host_sched_finalize;
    lat_host_sched_task_fn_t        lat_module_host_sched_task;
    lat_host_copy_file_fn_t         lat_module_host_copy_file;
    lat_host_move_file_fn_t         lat_module_host_move_file;
    lat_meta_sched_init_fn_t        lat_module_meta_sched_init;
    lat_meta_sched_finalize_fn_t    lat_module_meta_sched_finalize;
    lat_meta_sched_task_fn_t        lat_module_meta_sched_task;
    lat_meta_sched_workflow_fn_t    lat_module_meta_sched_workflow;
};
typedef struct lat_module_t lat_module_t;

extern lat_module_t lat_module;

#endif /* LAT_SCHED_H */
