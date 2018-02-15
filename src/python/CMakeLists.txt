project(starspace)

find_package(pybind11 2.2.1)

pybind11_add_module(starspace ${SOURCE_FILES} starspace_wrapper.cpp)
