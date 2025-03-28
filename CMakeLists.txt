cmake_minimum_required(VERSION 3.29)
project(soft_computing_practicals C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(soft_computing_practicals
        Back_Propogation_Network_For_XOR_Gate_For_Bipolar_Inputs_and_Targets.c)

target_link_libraries(soft_computing_practicals m)
