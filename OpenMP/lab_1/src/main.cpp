#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>

// No N Тип элемента вектора Тип операции
// 9 11 Без знаковый целый   Сложение векторов (a[i]=b[i]+c[i])

#define SIZE 11

template <class T>
void fill_vec_rand(T* vec, int size);

template <class T>
void display_vec(T* vec, int size);

int main() {
    ushort vec_a[SIZE];
    ushort vec_b[SIZE];
    ushort vec_c[SIZE];

    srand(time(NULL));
    fill_vec_rand(vec_b, SIZE);
    fill_vec_rand(vec_c, SIZE);

    for(int i = 0; i < SIZE; ++i)
        vec_a[i] = 0;

    std::cout << "Vector A" << std::endl;
    display_vec(vec_a, SIZE);
    std::cout << "Vector B" << std::endl;
    display_vec(vec_b, SIZE);
    std::cout << "Vector C" << std::endl;
    display_vec(vec_c, SIZE);

    #pragma omp parallel shared(vec_a,vec_b,vec_c)
    {
        #pragma omp for schedule(dynamic,1) nowait
        for (int i = 0; i < SIZE; ++i)
            vec_a[i] = vec_b[i] + vec_c[i];
    }

    std::cout << "Vector Result A" << std::endl;
    display_vec(vec_a, SIZE);
    return 0;
}

template <class T>
void fill_vec_rand(T* vec, int size){
    for(int i = 0; i < size; ++i)
        vec[i] = rand() % 254 + 1;
}

template <class T>
void display_vec(T* vec, int size){
    for(int i = 0; i < size; ++i)
        std::cout << "\tvec[" << i << "] = " << vec[i] << std::endl;
}