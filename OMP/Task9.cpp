#include <iostream>
#include <omp.h>

int main() {

    int width = 6;
    int height = 8;

    int d[width][height];

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            d[i][j] = 1 + rand() % 10;
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int max = -1;
    int min = 20;

    int thr1;
    int thr2;

#pragma omp parallel num_threads(3)
    for (int i = 0; i < width; i++) {

    #pragma omp for
        for (int j = 0; j < height; j++) {
            if (d[i][j] > max) {

                #pragma omp critical
                max = d[i][j];
            }
            if (d[i][j] < min) {

                #pragma omp critical
                min = d[i][j];
            }
        }
    }

    printf("Max is %d, min is %d\n", max, min);
}
