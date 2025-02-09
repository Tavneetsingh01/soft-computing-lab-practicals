cmake_minimum_required(VERSION 3.29)
project(soft_computing_practicals C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(soft_computing_practicals
        Adaline_Network_For_OR_Gate_Bipolar_Inputs_and_Targets.c)
