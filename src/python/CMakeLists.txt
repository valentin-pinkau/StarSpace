project(starspace)

add_subdirectory(pybind11)

pybind11_add_module(starspace ${SOURCE_FILES} starspace_wrapper.cpp)
