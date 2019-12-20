#include <iostream>
#include <omp.h>

int main() {
    int a[10] = {1,1,1,1,1,1,1,1,1,1};
    int b[10] = {2,2,2,2,2,2,2,2,2,2};

    int a_sum = 0, b_sum = 0;

    #pragma omp parallel for reduction(+: a_sum) reduction(+: b_sum)
    for (int i = 0; i < 10; i ++){
        a_sum += a[i];
        b_sum += b[i];
    }

    a_sum == b_sum ? printf("average value of a %f = average value of b %f", a_sum / 10.0, b_sum / 10.0) :
    a_sum > b_sum ? printf("average value of massive a: %f > average value of massive b: %f", a_sum / 10.0, b_sum / 10.0) :
    
    printf("average value of massive a: %f < average value of massive b: %f", a_sum / 10.0, b_sum / 10.0);
}