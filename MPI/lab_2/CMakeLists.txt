# Cmake Minimal
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME MpiLab_2)
# Set project
project(
    ${PROJECT_NAME}
    VERSION 1.0.0
    DESCRIPTION "
        Сгенерировать в каждом из N процессов вектор чисел. Размерность вектора
        – М. Произвести поэлементную обработку всех векторов и поместить
        результирующий вектор в каком-либо процессе. В работе использовать средства
        MPI для организации распределенных вычислений (см. раздел 1.8).
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