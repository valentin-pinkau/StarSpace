cmake_minimum_required(VERSION 3.7)
project(StarSpace)


find_package(Boost 1.63.0)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -funroll-loops")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O0 -fno-inline")

set(SOURCE_FILES
        src/utils/args.cpp
        src/utils/args.h
        src/utils/normalize.cpp
        src/utils/normalize.h
        src/utils/utils.cpp
        src/utils/utils.h
        src/data.cpp
        src/data.h
        src/dict.cpp
        src/dict.h
        src/doc_data.cpp
        src/doc_data.h
        src/doc_parser.cpp
        src/doc_parser.h
        src/matrix.h
        src/model.cpp
        src/model.h
        src/parser.cpp
        src/parser.h
        src/proj.cpp
        src/proj.h
        src/starspace.cpp
        src/starspace.h)

add_executable(StarSpace ${SOURCE_FILES} src/main.cpp)
add_executable(embed_doc ${SOURCE_FILES} src/apps/embed_doc.cpp)
add_executable(print_ngrams ${SOURCE_FILES} src/apps/print_ngrams.cpp)
add_executable(query_nn ${SOURCE_FILES} src/apps/query_nn.cpp)
add_executable(query_predict ${SOURCE_FILES} src/apps/query_predict.cpp)

add_subdirectory(src/python)
