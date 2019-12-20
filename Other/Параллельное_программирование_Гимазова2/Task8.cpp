#include <iostream>
#include <omp.h>
#include <time.h>

#define NUM 3

int main() {
    int A[NUM][NUM], B[NUM], C[NUM];
    int i, j;

    for (i = 0; i < NUM; i++) {
        for (j = 0; j < NUM; j++) {
            A[i][j] = 1 + rand() % 10;
            B[i] = 1 * (i + 1);
            C[i] = 0;
        }
    }

    printf("Matrix A and vector B: \n");
    for (i = 0; i < NUM; i++) {
        printf("A[%d]= ", i);
        for (j = 0; j < NUM; j++) {
            printf("%d ", A[i][j]);
        }
        printf("  B[%d]= %d \n", i, B[i]);
    }


    // последовательный алгоритм
    printf("sequential algorithm \n");

    //устанавливаем нулевой указатель
    srand(time(0));

    for (i = 0; i < NUM; i ++){
        for (j = 0; j < NUM; j ++){
            C[i] += A[i][j] * B[j];
        }
        printf("C[%d]=%d \n", i, C[i]);

        C[i] = 0;
    }
    // замеренное время последовательного алгоритма
    printf("time in sequential algorithm %f \n", clock() / 1000.0);


    omp_set_num_threads(NUM);

    //устанавливаем нулевой указатель
    srand(time(0));
    #pragma omp parallel
    {
        #pragma omp for
            for (i = 0; i < NUM; i++) {
                for (j = 0; j < NUM; j++)
                    C[i] += (A[i][j] * B[j]);
                /*Критическая секция предотвращает множественный одновременный доступ к данному сегменту кода*/
                #pragma omp critical
                    printf("num of thread = %d i = %d C[%d] = %d \n", omp_get_thread_num(), i, i, C[i]);

            }
    }
    // замеренное время парарллельного алгоритма
    printf("time in parallel algorithm %f", clock() / 1000.0);
}

