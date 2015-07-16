#include <Python.h>

/*
 * Public APIs accessible from Python code
 */
static PyObject* py_device_sched_init (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_device_sched_finalize (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_device_sched_task (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_host_sched_init (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_host_sched_finalize (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_host_sched_task (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_host_copy_file (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_host_move_file (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_meta_sched_init (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_meta_sched_finalize (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
}

static PyObject* py_meta_sched_task (PyObject *self, PyObject *args)
{
    Py_buffer *buf_ret = NULL;

    return Py_BuildValue ("z*", buf_ret);
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
    {"lat_host_sched_copy_file", py_host_sched_copy_file, METH_VARARGS},
    {"lat_host_sched_move_file", py_host_sched_move_file, METH_VARARGS},
    {"lat_meta_sched_init", py_meta_sched_init, METH_VARARGS},
    {"lat_meta_sched_finalize", py_meta_sched_finalize, METH_VARARGS},
    {"lat_meta_sched_task", py_meta_sched_task, METH_VARARGS},
};
