# Cmake Minimal
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME OpenMP_Lab_2)
# Set project
project(
    ${PROJECT_NAME}
    VERSION 1.0.0
    DESCRIPTION "
        Реализовать и распараллелить с помощью OpenMP различные алгоритмы.
    "
)
# Set compilers
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
# Add include directories
include_directories(./inc)
# Add OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
# Set Source Files
set(SOURCE_FILES
    ./src/main.cpp
)
# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MPI_C_LIBRARIES})