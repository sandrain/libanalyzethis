#include <Python.h>
#include "lat_constants.h"

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
    int rc = LAT_SUCCESS;

    return Py_BuildValue ("i", rc);
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
