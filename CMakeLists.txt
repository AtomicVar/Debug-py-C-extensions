cmake_minimum_required(VERSION 3.4...3.27)
project(hello)

find_package(pybind11)

pybind11_add_module(hello hello.cpp)