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
    int         rc          = LAT_SUCCESS;
    char        **files_out = NULL;
    char        *file_in    = NULL;
    PyObject    *list       = NULL;
    int         i;
    int         n_files_out;

    if (lat_module.lat_module_meta_sched_workflow != NULL) {
        if (!PyArg_ParseTuple (args, "s", &file_in)) {
            rc = LAT_ERROR;
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
    }

    /* XXX figure out how we can safely free file_out. Note that Python can
           retain a variable, it might be a solution here */

    return list;
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
