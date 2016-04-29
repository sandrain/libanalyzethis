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

#include <stdbool.h>
#include <Python.h>

#include "lat_constants.h"
#include "lat_sched.h"
#include "lat_debug.h"

lat_device_t        *lat_device         = NULL;
lat_device_sched_t  *lat_device_sched   = NULL;
lat_host_t          *lat_host           = NULL;
lat_host_sched_t    *lat_host_sched     = NULL;
lat_cluster_t       *lat_cluster        = NULL;
lat_meta_sched_t    *lat_meta_sched     = NULL;

/*
 * Public APIs accessible from Python code
 */
static PyObject*
py_sched_module_init (PyObject *self, PyObject *args)
{
    int         rc      = LAT_SUCCESS;
    long        argc;
    int         i;
    char        **c_argv;

    rc = lat_init_module();
    if (rc != LAT_SUCCESS) {
        LAT_ERR_MSG (("Cannot initialize the module"));
        rc = LAT_ERROR;
        goto fn_exit;
    }

    if (lat_module.lat_module_init == NULL) {
        rc = LAT_ERROR;
        goto fn_exit;
    }

    if (!PyTuple_Check (args)) {
        argc = 1;
        c_argv = malloc (sizeof (char*));
        c_argv[0] = PyString_AsString (args);
    } else {
        PyObject *v;

        argc = PyTuple_Size (args);
        c_argv = malloc (argc * sizeof (char*));
        for (i = 0; i < argc; i++) {
            v = PyTuple_GetItem (args, i);
            c_argv[i] = PyString_AsString (v);
        }
    }

    /* Yes we do an ugly cast from long to int. No point to find a better
       solution for now, the number should be small. */
    rc = lat_module.lat_module_init ((int)argc, c_argv);
    if (rc != LAT_SUCCESS) {
        goto fn_exit;
    }

    lat_device  = &lat_module.syscfg->server_cfg[0].afes_cfg[0];
    lat_host    = &lat_module.syscfg->server_cfg[0];

 fn_exit:
    return Py_BuildValue ("i", rc); 
}

static PyObject*
py_sched_module_finalize (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
}

static PyObject*
py_device_sched_init (PyObject *self, PyObject *args)
{
    int                 rc = LAT_SUCCESS;

    if (lat_module.lat_module_device_sched_init == NULL) {
        rc = LAT_ERROR;
        goto exit_fn;
    }

    rc = lat_module.lat_module_device_sched_init (lat_device,
                                                  &lat_device_sched);
    if (rc != LAT_SUCCESS) {
        LAT_ERR_MSG (("lat_module_device_sched_init() failed"));
        goto exit_fn;
    }

    if (lat_device_sched == NULL) {
        LAT_ERR_MSG (("Invalid device scheduler object"));
        rc = LAT_ERROR;
        goto exit_fn;
    }

 exit_fn:
    return Py_BuildValue ("i", rc);
}

static PyObject*
py_device_sched_finalize (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
}

static PyObject*
py_device_sched_task (PyObject *self, PyObject *args)
{
    int         rc;
    lat_core_t  *core;
    int         core_id = -1;
    lat_task_t  *task   = NULL;

    if (lat_module.lat_module_device_sched_task == NULL) {
        rc = LAT_ERROR;
        goto exit_fn;
    }

    rc = lat_module.lat_module_device_sched_task (lat_device_sched,
                                                  task,
                                                  &core);
    if (rc != LAT_SUCCESS) {
        LAT_ERR_MSG (("lat_module_device_sched_task() failed"));
        goto exit_fn;
    }

    /* XXX some uglyness for now: we go back to python, we break the idea of
           having an opaque handle, explicitly cast the value and return it */

    core_id = (int)*core;

 exit_fn:
    return Py_BuildValue ("i", core_id);
}

static PyObject*
py_host_sched_init (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

    if (lat_module.lat_module_host_sched_init == NULL) {
        rc = LAT_ERROR;
        goto exit_fn;
    }

    rc = lat_module.lat_module_host_sched_init (lat_host,
                                                &lat_host_sched);
    if (rc != LAT_SUCCESS) {
        LAT_ERR_MSG (("lat_module_host_sched_init() failed"));
        goto exit_fn;
    }

    if (lat_host_sched == NULL) {
        LAT_ERR_MSG (("Invalid host scheduler object"));
        rc = LAT_ERROR;
        goto exit_fn;
    }

 exit_fn:
    return Py_BuildValue ("i", rc);
}

static PyObject*
py_host_sched_finalize (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
}

static PyObject*
py_host_sched_task (PyObject *self, PyObject *args)
{
    int             rc      = LAT_SUCCESS;
    lat_device_t    *afe    = NULL;
    int             afe_id  = -1;
    lat_task_t      *task   = NULL;

    if (lat_module.lat_module_host_sched_task == NULL)
        goto exit_fn;

    rc = lat_module.lat_module_host_sched_task (lat_host_sched,
                                                task,
                                                &afe);
    if (rc != LAT_SUCCESS) {
        LAT_ERR_MSG (("lat_module_device_sched_task() failed"));
        goto exit_fn;
    }

    afe_id = (int)afe->dev_id;

 exit_fn:
    return Py_BuildValue ("i", afe_id);
}

static PyObject*
py_host_sched_file (PyObject *self, PyObject *args)
{
    int             rc      = LAT_SUCCESS;
    lat_device_t    *afe    = NULL;
    int             afe_id  = -1;
    lat_file_t      *file   = NULL;

    if (lat_module.lat_module_host_sched_file == NULL)
        goto exit_fn;

    rc = lat_module.lat_module_host_sched_file (lat_host_sched,
                                                file,
                                                &afe);
    if (rc != LAT_SUCCESS) {
        LAT_ERR_MSG (("lat_module_device_sched_file() failed"));
        goto exit_fn;
    }

    afe_id = (int)afe->dev_id;

 exit_fn:
    return Py_BuildValue ("i", afe_id);
}

static PyObject*
py_host_sched_file (PyObject *self, PyObject *args)
{
    int             rc      = LAT_SUCCESS;
    lat_device_t    *afe    = NULL;
    int             afe_id  = -1;
    lat_file_t      *file   = NULL;

    if (lat_module.lat_module_host_sched_file == NULL)
        goto exit_fn;

    rc = lat_module.lat_module_host_sched_file (lat_host_sched,
                                                file,
                                                &afe);
    if (rc != LAT_SUCCESS)
        LAT_ERR_MSG (("lat_module_device_sched_task() failed"));

    afe_id = (int)afe->dev_id;

 exit_fn:
    return Py_BuildValue ("i", afe_id);
}

static PyObject*
py_host_copy_file (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
}

static PyObject*
py_host_move_file (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
}

static PyObject*
py_meta_sched_init (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

    if (lat_module.lat_module_meta_sched_init == NULL) {
        rc = LAT_ERROR;
        goto exit_fn;
    }

    rc = lat_module.lat_module_meta_sched_init (lat_cluster,
                                                &lat_meta_sched);
    if (rc != LAT_SUCCESS) {
        LAT_ERR_MSG (("lat_module_meta_sched_init() failed"));
        goto exit_fn;
    }

    if (lat_meta_sched == NULL) {
        LAT_ERR_MSG (("Invalid meta scheduler object"));
        rc = LAT_ERROR;
        goto exit_fn;
    }

 exit_fn:
    return Py_BuildValue ("i", rc);
}

static PyObject*
py_meta_sched_finalize (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
}

static PyObject*
py_meta_sched_task (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;
    lat_host_t  *host;
    int         host_id = -1;
    lat_task_t  *task;

    if (lat_module.lat_module_meta_sched_task == NULL)
        goto exit_fn;

    rc = lat_module.lat_module_meta_sched_task (lat_meta_sched,
                                                task,
                                                &host);
    if (rc != LAT_SUCCESS) {
        LAT_ERR_MSG (("lat_module_meta_sched_task() failed"));
        goto exit_fn;
    }

 exit_fn:
    return Py_BuildValue ("i", rc);
}

static PyObject*
py_meta_sched_file (PyObject *self, PyObject *args)
{
    int         rc      = LAT_SUCCESS;
    lat_host_t  *host   = NULL;
    int         host_id = -1;
    lat_file_t  *file   = NULL;

    if (lat_module.lat_module_meta_sched_file == NULL)
        goto exit_fn;

    rc = lat_module.lat_module_meta_sched_file (lat_meta_sched,
                                                file,
                                                &host);
    if (rc != LAT_SUCCESS) {
        LAT_ERR_MSG (("lat_module_meta_sched_file() failed"));
        goto exit_fn;
    }

    host_id = (int)host->host_id;

 exit_fn:
    return Py_BuildValue ("i", rc);
}

static PyObject*
py_meta_sched_file (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
}

static PyObject*
py_meta_sched_workflow (PyObject *self, PyObject *args)
{
    int         rc          = LAT_SUCCESS;
    char        **files_out = NULL;
    char        *file_in    = NULL;
    PyObject    *list       = NULL;
    int         i;
    int         n_files_out;

    if (lat_module.lat_module_meta_sched_workflow != NULL) {
        if (!PyArg_ParseTuple (args, "s", &file_in)) {
            rc = LAT_ERROR;
            files_out = NULL;
        } else {
            rc = lat_module.lat_module_meta_sched_workflow (file_in,
                                                            &n_files_out,
                                                            &files_out);
            if (rc != LAT_SUCCESS) {
                fprintf (stderr,
                         "[%s:%d] ERROR: lat_module_meta_sched_workflow() "
                         "failed\n",
                         __func__, __LINE__);
            } else {
                if (list == NULL) {
                    list = PyList_New(n_files_out);
                }

                for (i = 0; i < n_files_out; i++) {
                    PyObject *f = PyString_FromString (files_out[i]);
                    if (f == NULL) {
                        fprintf (stderr,
                                 "[%s:%d] ERROR: PyString_FromString() failed\n",
                                 __func__, __LINE__);
                        return NULL;
                    }
                    PyList_SET_ITEM (list, i, f);
                }
            }
        }
    } else {
        rc = LAT_NOT_IMPL;
        files_out = NULL;
    }

    /* XXX figure out how we can safely free the memory that has been allocated.
           Note that Python can retain a variable, it might be a solution here.
     */

    return list;
}

/*
 * Bind python/C functions
 */
static PyMethodDef pythonSched_methods[] = {
    {"lat_module_init", py_sched_module_init, METH_VARARGS},
    {"lat_module_finalize", py_sched_module_finalize, METH_VARARGS},
    {"lat_device_sched_init", py_device_sched_init, METH_VARARGS},
    {"lat_device_sched_finalize", py_device_sched_finalize, METH_VARARGS},
    {"lat_device_sched_task", py_device_sched_task, METH_VARARGS},
    {"lat_host_sched_init", py_host_sched_init, METH_VARARGS},
    {"lat_host_sched_finalize", py_host_sched_finalize, METH_VARARGS},
    {"lat_host_sched_task", py_host_sched_task, METH_VARARGS},
    {"lat_host_sched_file", py_host_sched_file, METH_VARARGS},
    {"lat_host_copy_file", py_host_copy_file, METH_VARARGS},
    {"lat_host_move_file", py_host_move_file, METH_VARARGS},
    {"lat_meta_sched_init", py_meta_sched_init, METH_VARARGS},
    {"lat_meta_sched_finalize", py_meta_sched_finalize, METH_VARARGS},
    {"lat_meta_sched_task", py_meta_sched_task, METH_VARARGS},
    {"lat_meta_sched_file", py_meta_sched_file, METH_VARARGS},
    {"lat_meta_sched_workflow", py_meta_sched_workflow, METH_VARARGS},
};

PyMODINIT_FUNC
initpy_lat_module (void)
{
    (void) Py_InitModule ("py_lat_module", pythonSched_methods);
}
