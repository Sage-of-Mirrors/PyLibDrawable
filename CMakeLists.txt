cmake_minimum_required(VERSION 3.4...3.18)
project(pylibdrawable LANGUAGES CXX)

add_subdirectory(extern/libdrawable)

add_subdirectory(extern/pybind11)
pybind11_add_module(pylibdrawable PyLibDrawable.cpp)

target_include_directories(pylibdrawable PUBLIC extern/libdrawable/include)
target_link_libraries(pylibdrawable PRIVATE libdrawable)