#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <ctime> 
#include <iostream>
#include <chrono>
#define arrLength 100000
int main(int argc, char** argv)
{
    int arr[arrLength];
    int i;
    for (i = 0; i < arrLength; i++)
    {
        arr[i] = i+1;
    }
    auto start = std::chrono::high_resolution_clock::now();
    int sum = 0;
    for (i = 0; i < arrLength; i++)
    {
        sum += arr[i];
    }
    printf("sum  by serial =  %d \n", sum);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
    sum = 0;

    start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(4)
        for (i = 0; i < arrLength; i++)
        {
  
#pragma omp critical
                {
                sum += arr[i];
                }

        }
  
    printf("sum by critical =  %d \n", sum);
    finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";


    sum = 0;
    
    start = std::chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(4)
    {
        int sum_th = 0;
#pragma omp  for
        for (i = 0; i < arrLength; i++)
    {
            sum_th = sum_th + i;
    }

#pragma omp atomic
            sum += sum_th;

    }

    printf("sum by atomic =  %d \n", sum);
    finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";


    sum = 0;
    start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for  default(shared) private(i)  num_threads(4)    reduction(+:sum)

        for (i = 0; i < arrLength; i++)
            sum = sum + i;

        printf("sum by reduction =  %d \n", sum);
        finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
    return 0;
}
