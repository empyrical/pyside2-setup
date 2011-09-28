/*
 * This file is part of the Shiboken Python Bindings Generator project.
 *
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: PySide team <contact@pyside.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "sbkstring.h"

namespace Shiboken
{

namespace String
{

bool check(PyObject* obj)
{
    return obj == Py_None ||
#if PY_MAJOR_VERSION >= 3
        PyUnicode_Check(obj);
#else
        PyString_Check(obj);
#endif
}

bool convertible(PyObject* obj)
{
    return check(obj);
}

PyObject* fromCString(const char* value)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromString(value);
#else
    return PyBytes_FromString(value);
#endif
}

const char* toCString(PyObject* str)
{
#if PY_MAJOR_VERSION >= 3
    return _PyUnicode_AsString(str);
#else
    return PyBytes_AS_STRING(str);
#endif
}

bool concat(PyObject** val1, PyObject* val2)
{
#if PY_MAJOR_VERSION >= 3
    PyObject* result = PyUnicode_Concat(*val1, val2);
    Py_DECREF(*val1);
    *val1 = result;
    return true;
#else
    return false;
#endif
}

PyObject* fromFormat(const char* format, ...)
{
    va_list argp;
    va_start(argp, format);
    PyObject* result = 0;
#if PY_MAJOR_VERSION >= 3
    result = PyUnicode_FromFormatV(format, argp);
#else
    result = PyString_FromFormatV(format, argp);
#endif
    va_end(argp);
    return result;
}

PyObject* fromStringAndSize(const char* str, Py_ssize_t size)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromStringAndSize(str, size);
#else
    return PyString_FromStringAndSize(str, size);
#endif
}

int compare(PyObject* val1, const char* val2)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_CompareWithASCIIString(val1, val2);
#else
    return strcmp(PyString_AS_STRING(X), Y);
#endif
}

Py_ssize_t len(PyObject* str)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_GET_SIZE(str);
#else
    return PyString_GET_SIZE(str);
#endif

}

} // namespace String

} // namespace Shiboken