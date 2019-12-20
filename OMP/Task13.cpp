#include <iostream>
#include <omp.h>
#include <cmath>

#define NUM 30
int main() {
    int a[NUM] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
    double dec_num = 0;
    omp_set_num_threads(3);
    
#pragma omp parallel for reduction(+: dec_num)
    for (int i = NUM - 1; i >= 0; i --){
        dec_num += a[i] * pow(2, NUM - (1 + i)); //
        printf("Dec_num = %f, thread = %d \n", dec_num, omp_get_thread_num());
    }
    printf("\n");
    printf("Result = %f", dec_num);
}


















































