cmake_minimum_required(VERSION 3.7)
project(StarSpace)


find_package(Boost 1.63.0)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -funroll-loops")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O0 -fno-inline")

set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/args.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/args.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/normalize.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/normalize.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/data.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/data.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dict.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dict.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/doc_data.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/doc_data.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/doc_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/doc_parser.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/proj.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/proj.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/starspace.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/starspace.h)

add_executable(StarSpace ${SOURCE_FILES} src/main.cpp)

add_subdirectory(src/apps)

