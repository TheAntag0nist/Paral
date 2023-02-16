#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>
#include <mpi.h>

#define M 40

// Вариант - 9
// Вар M N  Data Type          Operation
//  9  6 40 Без знаковый целый Двоичное И
// mpiexec -n 5 --oversubscribe MpiLab_2

int main(int argc, char **argv) {
    std::vector<uint32_t> result;
    int process_rank = 0;
    int process_cnt = 0;

    result.resize(M);
    srand(time(NULL));

    // 1. Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_cnt);

    // Fill array 
    std::vector<uint32_t> inner_values;
        for(int i = 0; i < M; ++i)
            inner_values.push_back(rand() % 128 + 32 + process_rank);

    // Display array
    for(auto val : inner_values)
        std::cout << "[Process rank " << process_rank << "]:> " << val << std::endl;
    
    // Global Binary AND
    MPI_Reduce(
        inner_values.data(), result.data(), 
        M, MPI_INT, MPI_BAND, 0, MPI_COMM_WORLD
    ); 
    // Process Synchronization
    MPI_Barrier(MPI_COMM_WORLD);

    // Display result value
    if(process_rank == 0){
        std::cout << std::endl;
        for(auto val : result)
            std::cout << "[Process rank 0]:> " << val << std::endl;
    }

    // 2. Finalize MPI
    MPI_Finalize();
    return 0;
}