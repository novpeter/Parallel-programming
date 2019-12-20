#include <iostream>
#include <omp.h>

int main() {
    int num = 210;
    int sqr_num = 0;
    int a = 1;
    omp_set_num_threads(3);
    
    #pragma omp parallel for reduction(+:sqr_num)
        for (int i = 1; i <= num; i ++){
            sqr_num += a;
            a += 2;
        }

    printf("%d ", sqr_num);
}
