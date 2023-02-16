#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>
#include <mpi.h>

#define M 3
#define N 10

// Вариант - 9
// Вар M N  Data Type          Тип сортировки
//  9  3 10 Без знаковый целый По убыванию
// mpiexec -n 10 --oversubscribe MpiLab_3

void bubble_sort(std::vector<uint32_t>& vec);

void deallocate_matrix(uint32_t** matrix, int rows);
uint32_t**  allocate_matrix(int rows, int cols);

void fill_matrix_rnd(uint32_t** ptr, int rows, int cols);
void display_matrix(uint32_t** ptr, int rows, int cols);

static int process_rank = 0;
static int process_cnt = 0;

int main(int argc, char **argv) {
    // 0. Basic Data 
    std::vector<uint32_t> data_vec;
    std::vector<uint32_t> temp_vec;
    uint32_t** matrix;
    uint32_t** result;

    srand(time(NULL));
    
    // 1. Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_cnt);

    int split_size = M;
    while(split_size * process_cnt < M * N){
        split_size += 3;
    }

    if(process_rank == 0)
        std::cout << "Split size: " << split_size << std::endl;

    data_vec.resize(split_size * process_cnt);
    temp_vec.resize(split_size);

    // 2. Generate matrix
    if(process_rank == 0){
        std::cout << "[Process rank: 0]" << std::endl;
        
        matrix = allocate_matrix(N, M);
        result = allocate_matrix(N, M);

        fill_matrix_rnd(matrix, N, M);
        display_matrix(matrix, N, M);
    
        int counter = 0;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                data_vec[counter] = matrix[i][j];
                ++counter;
            }
        }
    }


    // 3. Send Cols to other processes
    MPI_Scatter(
        data_vec.data(), split_size, MPI_INT,
        temp_vec.data(), split_size, MPI_INT,
        0, MPI_COMM_WORLD
    );

    for(int i = 0; i < split_size / M; ++i){
        std::vector<uint32_t> tmp;
        tmp.push_back(temp_vec[i * M]);
        tmp.push_back(temp_vec[i * M + 1]);
        tmp.push_back(temp_vec[i * M + 2]);

        bubble_sort(tmp);

        temp_vec[i * M] = tmp[0];
        temp_vec[i * M + 1] = tmp[1];
        temp_vec[i * M + 2] = tmp[2];
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(
        temp_vec.data(), temp_vec.size(), MPI_INT,
        data_vec.data(), temp_vec.size(), MPI_INT,
        0, MPI_COMM_WORLD
    );
    MPI_Barrier(MPI_COMM_WORLD);
    
    if(process_rank == 0){
        std::cout << "[Process rank: 0]" << std::endl;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j)
                result[i][j] = data_vec[i * M + j];

        display_matrix(result, N, M);
        deallocate_matrix(matrix, N);
        deallocate_matrix(result, N);
    }
    
    // 2. Finalize MPI
    MPI_Finalize(); 
    return 0;
}

uint32_t**  allocate_matrix(int rows, int cols){
    uint32_t** matrix = new uint32_t*[rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new uint32_t[cols];

    return matrix;
}

void deallocate_matrix(uint32_t** matrix, int rows){
    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

void fill_matrix_rnd(uint32_t** ptr, int rows, int cols){
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j)
            ptr[i][j] = rand() % 10 + 32 + process_rank;
    }
}

void display_matrix(uint32_t** ptr, int rows, int cols){
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j){
            if(j % M == 0)
                std::cout << "  ";
            std::cout << ptr[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}

void bubble_sort(std::vector<uint32_t>& vec){
    bool bubble_sort_fl = true;

    while(bubble_sort_fl){
        bubble_sort_fl = false;

        for(int i = 0; i < vec.size() - 1; ++i){
            if(vec[i] < vec[i + 1]){
                auto temp = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = temp;
                bubble_sort_fl = true;
            }
        }
    }
}