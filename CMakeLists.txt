cmake_minimum_required(VERSION 3.19)
project(editpgm C)

set(CMAKE_C_STANDARD 99)

add_executable(editpgm src/main.c src/lib/pgm.c src/lib/pgm.h src/mirrHor.c src/mirror_vertical.c src/invert.c)

find_package(OpenMP)
if(OpenMP_C_FOUND)
    target_link_libraries(editpgm PUBLIC OpenMP::OpenMP_C)
endif()