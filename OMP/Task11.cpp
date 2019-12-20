#include <iostream>
#include <omp.h>

int main() {
    int a[40];
    int max = -1;

    for (int i = 0; i < 40; i++) {
        a[i] = 1 + rand() % 50;
        printf("%d ", a[i]);
    }
    printf("\n");

    omp_set_num_threads(3);

    #pragma omp parallel for
    for (int i = 0; i < 40; i ++){
        if (a[i] % 7 == 0 && a[i] > max){
            #pragma omp critical
                max = a[i];
        }
    }

    printf("Max = %d", max);
}
