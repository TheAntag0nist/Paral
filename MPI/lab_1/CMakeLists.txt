# Cmake Minimal
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME MpiLab_1)
# Set project
project(
    ${PROJECT_NAME}
    VERSION 1.0.0
    DESCRIPTION "
            Переслать вектор, размерности M, N процессам, используя различные виды
        связи между процессами. Элементы вектора задаются произвольно. Элементы
        вектора пересылаемого и принятого вектора, а также время выполнения должны
        быть выведены на экран.
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