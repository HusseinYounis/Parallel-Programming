#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define arrLength 100
int main(int argc, char** argv)
{
    int arr[arrLength];
    int i;
    for (i = 0; i < arrLength; i++)
    {
        arr[i] = i+1;
    }

    int max = arr[0];
    for (i = 1; i < arrLength; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    printf("max number by serial =  %d \n", max);

    max = arr[0];
#pragma omp parallel for num_threads(4)
        for (i = 1; i < arrLength; i++)
        {
            if (arr[i] > max)
            {
#pragma omp critical
                {
                    max = arr[i];
                }
                
            }
        }
  
    printf("max number by parallel =  %d \n", max);
    return 0;
}
