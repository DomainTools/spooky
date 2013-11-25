// This python module is a wrapper around Bob Jenkins' c++ implementation.

#include <stdio.h>
#include <string.h>
#include <Python.h>
#include "SpookyV2.h"

#ifdef _MSC_VER
  typedef unsigned __int64 uint64;
#else
# include <stdint.h>
  typedef uint64_t uint64;
#endif

struct module_state {
  PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

static PyObject *
spooky_hash128_bytes(PyObject *self, PyObject *args, PyObject *kwargs)
{
    const char *message;
    int message_length;
    uint64 seed[2] = {0};

    static char *kwlist[] = {(char *)"message", (char *)"seed",
        NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s#|K", kwlist,
        &message, &message_length, &seed)) {
        return NULL;
    }

    seed[1] = seed[0];

    SpookyHash::Hash128(message, message_length, &seed[0], &seed[1]);

    PyObject *retval = PyBytes_FromStringAndSize((const char *)seed, 16);
    return retval;
}

static PyObject *
spooky_hash128(PyObject *self, PyObject *args, PyObject *kwargs)
{
    const char *message;
    int message_length;
    uint64 seed[2] = {0};

    static char *kwlist[] = {(char *)"message", (char *)"seed",
        NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s#|K", kwlist,
        &message, &message_length, &seed)) {
        return NULL;
    }

    seed[1] = seed[0];

    SpookyHash::Hash128(message, message_length, &seed[0], &seed[1]);

    PyObject *retval = _PyLong_FromByteArray((unsigned char *)seed, 16, 1, 0);
    return retval;
}

static PyObject *
spooky_hash64(PyObject *self, PyObject *args, PyObject *kwargs)
{
    const char *message;
    int message_length;
    uint64 seed[2] = {0};

    static char *kwlist[] = {(char *)"message", (char *)"seed",
        NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s#|K", kwlist,
        &message, &message_length, &seed)) {
        return NULL;
    }

    seed[1] = seed[0];

    SpookyHash::Hash128(message, message_length, &seed[0], &seed[1]);

    PyObject *retval = _PyLong_FromByteArray((unsigned char *)seed, 8, 1, 0);
    return retval;
}

static PyObject *
spooky_hash32(PyObject *self, PyObject *args, PyObject *kwargs)
{
    const char *message;
    int message_length;
    uint64 seed[2] = {0};

    static char *kwlist[] = {(char *)"message", (char *)"seed",
        NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s#|K", kwlist,
        &message, &message_length, &seed)) {
        return NULL;
    }

    seed[1] = seed[0];

    SpookyHash::Hash128(message, message_length, &seed[0], &seed[1]);

    PyObject *retval = _PyLong_FromByteArray((unsigned char *)seed, 4, 1, 0);
    return retval;
}

static PyMethodDef SpookyMethods[] = {
    {"hash128_bytes", (PyCFunction)spooky_hash128_bytes,
      METH_VARARGS | METH_KEYWORDS,
        "Generate a 128bit hash as bytes"},
    {"hash128", (PyCFunction)spooky_hash128,
      METH_VARARGS | METH_KEYWORDS,
        "Generate a 128bit int hash."},
    {"hash64", (PyCFunction)spooky_hash64,
      METH_VARARGS | METH_KEYWORDS,
        "Generate a 64bit int hash."},
    {"hash32", (PyCFunction)spooky_hash32,
      METH_VARARGS | METH_KEYWORDS,
        "Generate a 32bit int hash."},
    {NULL, NULL, 0, NULL}
};

#if PY_MAJOR_VERSION >= 3

static int spooky_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int spooky_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef spooky = {
    PyModuleDef_HEAD_INIT,
    "spooky",
    "Wrapper for Bob Jenkins' SpookyHash V2",
    sizeof(struct module_state),
    SpookyMethods,
    NULL,
    spooky_traverse,
    spooky_clear,
    NULL
};

#define INITERROR return NULL

extern "C" {
PyMODINIT_FUNC
PyInit_spooky(void)

#else
#define INITERROR return

extern "C" {
void
initspooky(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&spooky);
#else
    PyObject *module = Py_InitModule("spooky", SpookyMethods);
#endif

    if (module == NULL)
        INITERROR;

    PyModule_AddStringConstant(module, "__version__", "2.0.0");

    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException((char *) "spooky.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
}
