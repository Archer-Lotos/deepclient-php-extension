#include "php.h"
#include <Python.h>

PHP_FUNCTION(make_deep_client) {
    char *token = NULL;
    char *url = NULL;
    size_t token_len, url_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(token, token_len)
        Z_PARAM_STRING(url, url_len)
    ZEND_PARSE_PARAMETERS_END();

    Py_Initialize();

    PyObject *pName = PyUnicode_DecodeFSDefault("deep_client_php_extension");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "make_deep_client");

        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pArgs = PyTuple_Pack(2, Py_BuildValue("s", token), Py_BuildValue("s", url));

            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != NULL) {
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

PHP_FUNCTION(test_python) {
    Py_Initialize();

    PyObject *pName = PyUnicode_DecodeFSDefault("deep_client_php_extension");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "test_python");

        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pValue = PyObject_CallObject(pFunc, NULL);

            if (pValue != NULL) {
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

static zend_function_entry deep_client_php_extension_functions[] = {
    PHP_FE(make_deep_client, NULL)
    PHP_FE(test_python, NULL)
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