#include <iostream>
#include <omp.h>

int main() {
    int a[30];
    int count_9 = 0;

    for (int i = 0; i < 30; i ++){
        a[i] = 1 + rand() % 10;
        printf("%d  ", a[i]);
    }

    printf("\n");

#pragma omp parallel num_threads(3)
    {
    #pragma omp for
        for (int i = 0; i < 30; i++) {
            if (a[i] % 9 == 0) {

            #pragma omp atomic
                count_9 ++;
                printf("Threads = %d, thread = %d, count = %d  \n", omp_get_num_threads(), omp_get_thread_num(), count_9);
            }
        }
    }

    printf("Count is %d \n", count_9);
}
