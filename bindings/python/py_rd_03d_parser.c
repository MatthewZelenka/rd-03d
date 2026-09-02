#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <rd_03d_parser.h>
#include <target_parser.h>
/// testing

#include <structmember.h>

typedef struct {
    PyObject_HEAD
    target_t data;
} PyTargetObject;

static PyObject *
PyTarget_FromTarget(target_t *target)
{
    PyTargetObject *obj;

    obj = PyObject_New(PyTargetObject, &PyTargetType);
    if (obj == NULL)
        return NULL;

    obj->target = target;

    return (PyObject *)obj;
}

/* Read-only members */
static PyMemberDef MyStruct_members[] = {
    {"major", T_INT, offsetof(MyStructObject, major), READONLY,
     "read-only major"},
    {"minor", T_INT, offsetof(MyStructObject, minor), READONLY,
     "read-only minor"},
    {"bug", T_INT, offsetof(MyStructObject, bug), READONLY,
     "read-only bug"},
    {NULL}
};


static PyTypeObject MyStructType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "mymodule.MyStruct",
    .tp_basicsize = sizeof(MyStructObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "A struct with read-only members",
    .tp_new = MyStruct_new,
    .tp_dealloc = (destructor)MyStruct_dealloc,
    .tp_members = MyStruct_members,
};
















///

static PyObject *
py_version(PyObject *self, PyObject *args)
{
    return PyUnicode_FromString("1.23");
}


static PyMethodDef methods[] =
{
    {
        "version",
        py_version,
        METH_NOARGS,
        "Return parser version"
    },

    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef module =
{
    PyModuleDef_HEAD_INIT,
    "rd_03d_parser",
    "Python bindings for rd_03d_parser",
    -1,
    methods
};


PyMODINIT_FUNC PyInit_rd_03d_parser(void)
{
    PyObject *m;

    if (PyType_Ready(&MyStructType) < 0)
        return NULL;
    m = PyModule_Create(&module);
    if (m == NULL)
        return NULL;
    
    Py_INCREF(&MyStructType);
    if (PyModule_AddObject(m, "MyStruct",
                           (PyObject *)&MyStructType) < 0) {
        Py_DECREF(&MyStructType);
        Py_DECREF(m);
        return NULL;
    }
    return m;
}
