#include <Python.h>
#include "lat_constants.h"
#include "lat_sched.h"

/*
 * Public APIs accessible from Python code
 */
static PyObject*
py_device_sched_init (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

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
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
}

static PyObject*
py_host_sched_init (PyObject *self, PyObject *args)
{
    int rc = LAT_SUCCESS;

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
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
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

    return Py_BuildValue ("i", rc);
}

static PyObject*
py_meta_sched_workflow (PyObject *self, PyObject *args)
{
    int     rc              = LAT_SUCCESS;
    char    *file_out       = NULL;
    char    *file_in        = NULL;

    if (lat_module.lat_module_meta_sched_workflow != NULL) {
        if (!PyArg_ParseTuple (args, "s", &file_in)) {
            rc = LAT_ERROR;
        } else {
            rc = lat_module.lat_module_meta_sched_workflow (file_in, &file_out);
            if (rc != LAT_SUCCESS) {
                fprintf (stderr,
                         "[%s:%d] ERROR: lat_module_meta_sched_workflow() "
                         "failed\n",
                         __func__, __LINE__);
            } else {
                fprintf (stderr, "Output file: %s\n", file_out);
            }
        }
    } else {
        rc = LAT_NOT_IMPL;
    }

    /* XXX figure out how we can safely free file_out. Note that Python can
           retain a variable, it might be a solution here */

    return Py_BuildValue ("is", rc, file_out);
}

/*
 * Bind python/C functions
 */
static PyMethodDef pythonSched_methods[] = {
    {"lat_device_sched_init", py_device_sched_init, METH_VARARGS},
    {"lat_device_sched_finalize", py_device_sched_finalize, METH_VARARGS},
    {"lat_device_sched_task", py_device_sched_task, METH_VARARGS},
    {"lat_host_sched_init", py_host_sched_init, METH_VARARGS},
    {"lat_host_sched_finalize", py_host_sched_finalize, METH_VARARGS},
    {"lat_host_sched_task", py_host_sched_task, METH_VARARGS},
    {"lat_host_copy_file", py_host_copy_file, METH_VARARGS},
    {"lat_host_move_file", py_host_move_file, METH_VARARGS},
    {"lat_meta_sched_init", py_meta_sched_init, METH_VARARGS},
    {"lat_meta_sched_finalize", py_meta_sched_finalize, METH_VARARGS},
    {"lat_meta_sched_task", py_meta_sched_task, METH_VARARGS},
    {"lat_meta_sched_workflow", py_meta_sched_workflow, METH_VARARGS},
};

PyMODINIT_FUNC
initpy_lat_module (void)
{
    (void) Py_InitModule ("py_lat_module", pythonSched_methods);
}
