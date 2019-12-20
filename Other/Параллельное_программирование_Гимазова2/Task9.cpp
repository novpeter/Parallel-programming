/*
 Написать программу, в которой объявить и присвоить начальные значения элементам
двумерного массива d[6][8], для инициализации значений использовать генератор случайных
чисел. Используя конструкцию директивы omp parallel for и omp critical определить
минимальное и максимальное значения элементов двумерного массива. Количество нитей
задать самостоятельно. Результат выдать на экран.
*/

#include <iostream>
#include <omp.h>

int main() {

    int width = 6;
    int height = 8;

    int d[width][height];

    // инициализация массива рандомными значениями
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
    // распредление итераций цикла между несколькими потоками
    #pragma omp for
        for (int j = 0; j < height; j++) {
            if (d[i][j] > max) {
                /*Критическая секция предотвращает множественный одновременный доступ к данному сегменту кода*/
                #pragma omp critical
                max = d[i][j];
            }
            if (d[i][j] < min) {
                /*Критическая секция предотвращает множественный одновременный доступ к данному сегменту кода*/
                #pragma omp critical
                min = d[i][j];
            }
        }
    }
    printf("max is %d, min is %d\n", max, min);

}