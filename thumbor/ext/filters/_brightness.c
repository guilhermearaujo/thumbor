#include "filter.h"

static PyObject*
_brightness_apply(PyObject *self, PyObject *args)
{
    PyObject *buffer = NULL, *delta = NULL;

    if (!PyArg_UnpackTuple(args, "apply", 2, 2, &delta, &buffer)) {
        return NULL;
    }

    Py_ssize_t size = PyString_Size(buffer);
    unsigned char *ptr = (unsigned char *) PyString_AsString(buffer);
    long long_delta = PyInt_AsLong(delta);

    int i = 0, r, g, b;
    size -= 3;
    for (; i <= size; i += 3) {
        r = ptr[i];
        g = ptr[i + 1];
        b = ptr[i + 2];

        r += long_delta;
        g += long_delta;
        b += long_delta;

        r = ADJUST_COLOR(r);
        g = ADJUST_COLOR(g);
        b = ADJUST_COLOR(b);

        ptr[i] = r;
        ptr[i + 1] = g;
        ptr[i + 2] = b;
    }

    Py_INCREF(buffer);
    return buffer;
}

FILTER_MODULE(_brightness)