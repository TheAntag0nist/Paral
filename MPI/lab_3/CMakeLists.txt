# Cmake Minimal
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME MpiLab_3)
# Set project
project(
    ${PROJECT_NAME}
    VERSION 1.0.0
    DESCRIPTION "
        Произвести сортировку элементов в столбцах (или строках) матрицы
        размерности NxM, с использованием распределения вычислений между
        процессами средствами MPI.
        Замечание: Программа должна работать корректно на ЛЮБОМ количестве
        процессов. Матрица при этом НЕ ДОЛЖНА менять свои размеры.
    "
)
# Set compilers
set(CMAKE_C_COMPILER "mpicc")
set(CMAKE_CXX_COMPILER "mpic++")
# Add include directories
include_directories(./inc)
# Add MPI
find_package(MPI) #make it REQUIRED, if you want
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
# Set Source Files
set(SOURCE_FILES
    ./src/main.cpp
)
# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MPI_C_LIBRARIES})