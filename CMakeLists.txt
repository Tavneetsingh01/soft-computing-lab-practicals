cmake_minimum_required(VERSION 3.29)
project(soft_computing_practicals C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(soft_computing_practicals
        Max_Min_Composition_Of_Cartesian_Product_Matrices.c)

target_link_libraries(soft_computing_practicals m)
