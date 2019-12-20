#include <iostream>
#include <omp.h>
#include <cmath>

int main() {
    int first_number;
    int last_number;

    std::cout << "Enter the first number of the range";
    std::cin >> first_number;

    std::cout << "Enter the last number of the range";
    std::cin >> last_number;

    omp_set_num_threads(5);
    #pragma omp parallel for

    for (int i = first_number; i <= last_number; i ++) {
        if ((i != 1) && (sqrt(i) < 2)){
            printf("%d ", i);
        }

        for (int j = 2; j <= sqrt(i); j ++){
            if (i % j == 0){
                break;
            }
            else if (j + 1 > sqrt(i)){
                printf("%d ", i);
            }
        }
    }
}
