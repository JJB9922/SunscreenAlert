# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

set(CJSON_SRC ${CMAKE_CURRENT_LIST_DIR}/../lib/cJSON.c)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../lib)
file(GLOB_RECURSE app_sources ${CMAKE_CURRENT_LIST_DIR}/src/*.*)

idf_component_register(SRCS ${app_sources} ${CJSON_SRC})