#define PY_SSIZE_T_CLEAN
#include "php_headers/php.h"
#include <Python.h>
#include <stdlib.h>

PHP_FUNCTION(make_deep_client) {
    char *token = NULL;
    char *url = NULL;
    size_t token_len, url_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(token, token_len)
        Z_PARAM_STRING(url, url_len)
    ZEND_PARSE_PARAMETERS_END();

    PyObject *pName, *pModule, *sys, *path, *newPaths;
    int i;
    Py_Initialize();

    sys = PyImport_ImportModule("sys");
    path = PyObject_GetAttrString(sys, "path");

    newPaths = PyUnicode_Split(PyUnicode_FromString("./"), PyUnicode_FromWideChar(L":", 1), -1);

    for(i=0; i<PyList_Size(newPaths); i++) {
        PyList_Append(path, PyList_GetItem(newPaths, i));
    }

    Py_XDECREF(newPaths);
    Py_XDECREF(path);
    Py_XDECREF(sys);

    pName = PyUnicode_DecodeFSDefault("deep_client_python_extension");

    if (pName == NULL){
        fprintf(stderr,"No Python hook file found\n");
    }

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "make_deep_client");

        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pArgs = PyTuple_Pack(2, Py_BuildValue("s", token), Py_BuildValue("s", url));

            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != NULL) {
                zend_class_entry *deepClient_ce;
                zend_object *deepClient_php;

                if (instanceof_function(pValue, PyObject_Type)) {
                    deepClient_ce = zend_fetch_class_by_name(ZEND_STRL("DeepClient"));
                    object_init_ex(return_value, deepClient_ce);
                    deepClient_php = Z_OBJ_P(return_value);
                } else {
                    ZVAL_OBJ(return_value, (zend_object *)pValue);
                }

                if (deepClient_php) {
                    Py_INCREF(deepClient_php);
                }

                Py_DECREF(pValue);
            } else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                PyErr_Clear();
                return;
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }
    Py_Finalize();
}


ZEND_BEGIN_ARG_INFO(arginfo_make_deep_client, 0)
                ZEND_ARG_INFO(0, token)
                ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

static zend_function_entry deep_client_php_extension_functions[] = {
    PHP_FE(make_deep_client, arginfo_make_deep_client)
PHP_FE_END
};

zend_module_entry deep_client_php_extension_module_entry = {
    STANDARD_MODULE_HEADER,
    "deep_client_php_extension",
    deep_client_php_extension_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "1.0",
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(deep_client_php_extension)