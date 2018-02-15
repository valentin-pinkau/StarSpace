project(starspace)

find_package(pybind11 2.2.1)

pybind11_add_module(starspace starspace_wrapper.cpp)