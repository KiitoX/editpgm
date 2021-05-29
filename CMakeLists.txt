cmake_minimum_required(VERSION 3.19)
project(editpgm C)

set(CMAKE_C_STANDARD 99)

add_executable(editpgm main.c lib/pgm.c lib/pgm.h)

find_package(OpenMP)
if(OpenMP_C_FOUND)
    target_link_libraries(editpgm PUBLIC OpenMP::OpenMP_C)
endif()