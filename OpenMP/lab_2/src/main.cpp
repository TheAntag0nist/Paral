#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <ctime>
#include <omp.h>

// No Размерность Тип элемента данных  Алгоритм
// 9  90x60       Без знаковый целый   Сортировка столбцов матрицы по убыванию

#define N 15
#define M 5

uint32_t**  allocate_matrix(int rows, int cols);
void deallocate_matrix(uint32_t** matrix, int rows);
void fill_matrix_rnd(uint32_t** ptr, int rows, int cols);
void display_matrix(uint32_t** ptr, int rows, int cols);

template <class T>
void bubble_sort(T* vec, int size);

int main() {
    srand(time(NULL));
    uint32_t** matrix = allocate_matrix(N, M);
    int rows = N, cols = M;
    fill_matrix_rnd(matrix, N, M);

    std::cout << "Matrix before processing" << std::endl;
    display_matrix(matrix, N, M);

    #pragma omp parallel shared(matrix, rows, cols)
    {
        #pragma omp for schedule(dynamic,1) nowait
        for (int i = 0; i < N; ++i)
            bubble_sort(matrix[i], M);
    }

    std::cout << "Matrix after processing" << std::endl;
    display_matrix(matrix, N, M);

    deallocate_matrix(matrix, N);
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

template <class T>
void bubble_sort(T* vec, int size){
    bool bubble_sort_fl = true;

    while(bubble_sort_fl){
        bubble_sort_fl = false;

        for(int i = 0; i < size - 1; ++i){
            if(vec[i] < vec[i + 1]){
                auto temp = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = temp;
                bubble_sort_fl = true;
            }
        }
    }
}

void fill_matrix_rnd(uint32_t** ptr, int rows, int cols){
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j){
            ptr[i][j] = rand() % 10 + 32;
            //std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }
}

void display_matrix(uint32_t** ptr, int rows, int cols){
    for(int i = 0; i < cols; ++i) {
        for(int j = 0; j < rows; ++j){
            if(j % M == 0)
                std::cout << "  ";
            std::cout << ptr[j][i] << "   ";
        }
        std::cout << std::endl;
    }
}