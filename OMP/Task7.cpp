#include <iostream>
#include <omp.h>
#include <stdio.h>

int main() {
    int a[12], b[12], c[12];

    omp_set_num_threads(3);
    #pragma omp parallel
    {
        #pragma omp for schedule(static, 3)
            for (int i = 0; i < 12; i ++) {
                a[i] = i;
                b[i] = i;
                printf("Thread %d, num of threads %d, a[%d] = %d, b[%d] = %d\n",
                        omp_get_thread_num(), omp_get_num_threads(), i, a[i], i, b[i]);
            }
    }

    printf("Array a: ");
    
    for (int i:a) {
        printf("%d ", a[i]);
    }
    
    printf("\n");
    printf("Array b: ");
    
    for (int i:b) {
        printf("%d ", b[i]);
    }
    
    printf("\n");

    omp_set_num_threads(4);
    
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic, 4)
            for (int i = 0; i < 12; i++) {
                c[i] = a[i] + b[i];
                printf("Thread %d, num of threads %d, c[%d] = %d \n", omp_get_thread_num(), omp_get_num_threads(), i, c[i]);
            }

    }

    printf("Array c: ");

    for (int i = 0; i < 12; i ++) {
        printf("%d ", c[i]);
    } 

    printf("\n");
}
