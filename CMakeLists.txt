cmake_minimum_required(VERSION 3.0)
project(deep_client_php_extension)

set(CMAKE_CXX_STANDARD 11)

find_package(PythonLibs REQUIRED)

set(PHP_INCLUDE_DIR php_headers)
set(EXT_PHP_INCLUDE_DIR ext_php_headers)
set(ZEND_INCLUDE_DIR zend_headers)

include_directories(${PHP_INCLUDE_DIR})
include_directories(${EXT_PHP_INCLUDE_DIR})
include_directories(${ZEND_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(deep_client_php_extension MODULE deep_client_php_extension.c
        deep_client.c)

target_link_libraries(deep_client_php_extension ${PYTHON_LIBRARIES})