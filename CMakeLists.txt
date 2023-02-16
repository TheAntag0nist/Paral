cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME Paral)
# Set project
project(
    ${PROJECT_NAME}
    VERSION 1.0.0
    DESCRIPTION "Системы с параллельной обработкой информации"
)
# Set output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# MPI projects
add_subdirectory(./MPI/lab_1)
add_subdirectory(./MPI/lab_2)
add_subdirectory(./MPI/lab_3)
# OpenMP projects
add_subdirectory(./OpenMP/lab_1)
add_subdirectory(./OpenMP/lab_2)
