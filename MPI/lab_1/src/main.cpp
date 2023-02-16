#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <mpi.h>

// Вариант - 9
// Вар M N Function
//  9  7 5 MPI_Scatter
// mpiexec -n 5 --oversubscribe MpiLab_1

int main(int argc, char **argv) {
    // 0. Data zone
    std::vector<int> send_vector = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> recv_vector;
    int process_rank = 0;
    int process_cnt = 0;

    // 1. Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_cnt);
    
    // Resize vector and set message split size
    double value = ((double) send_vector.size() / process_cnt);
    int split_size = std::ceil(value + 0.5);
    recv_vector.resize(split_size);

    int temp = split_size * process_cnt;
    if(temp > send_vector.size()){
        for(int i = send_vector.size(); i < temp; ++i)
            send_vector.push_back(-1);
    }

    // Start time
    auto start_tm = MPI_Wtime();
    
    MPI_Scatter(send_vector.data(), split_size, MPI_INT, 
                recv_vector.data(), split_size, MPI_INT,
                0, MPI_COMM_WORLD
    );

    std::cout << "[Process Rank " << process_rank << "]:> " << "Recieved vector: \n";
    for(int  i = 0; i < recv_vector.size(); ++i)
        std::cout << "[Process Rank " << process_rank << "]:> " << "\trecv[" << i << "] = " << recv_vector[i] << std::endl;

    // End time
    auto end_tm = MPI_Wtime();
    std::cout << "[Process Rank " << process_rank << "]:> " << std::fixed << "Delta time: " << end_tm - start_tm << std::endl;

    // 2. Finalize MPI
    MPI_Finalize();
    return 0;
}