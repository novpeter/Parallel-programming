#include <iostream>
#include <omp.h>
#include <stdio.h>
/*
 * Написать программу, в которой определить две параллельные области, каждая из которых
содержит итерационную конструкцию for выполняющую инициализацию элементов
одномерных массивов целых чисел a[12], b[12] и c[12]. Число нитей перед первой областью
задать равным 3, перед второй – равным 4. Первая параллельная область выполняет
инициализацию элементов массивов a и b с использованием статического распределения
итераций, размер порции итераций выбрать самостоятельно, вторая параллельная область
выполняет инициализацию элементов массива c по следующему правилу c[i] = a[i] + b[i], с
использованием динамического распределения итераций, размер порции итераций выбрать
самостоятельно. В каждой области определить и выдать на экран количество нитей, номер
нити и результат выполнения цикла. Убедиться в правильности работы программы.
 */

int main() {

    int a[12], b[12], c[12];

    omp_set_num_threads(3);
    #pragma omp parallel
    {
        // в опции schedule параметр type задаем - static, кол-во итераций = 3
        // итерации цикла распределены по блокам, первый блок выполняет нулевая нить, второй - следующая и т.д.
        #pragma omp for schedule(static, 3)
            for (int i = 0; i < 12; i ++) {
                a[i] = i;
                b[i] = i;
                printf("thread %d, num of threads %d, a[%d] = %d, b[%d] = %d\n",
                        omp_get_thread_num(), omp_get_num_threads(), i, a[i], i, b[i]);
            }
    }

    printf("massive a: ");
    for (int i:a) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("massive b: ");
    for (int i:b) {
        printf("%d ", b[i]);
    }
    printf("\n");

    omp_set_num_threads(4);
    #pragma omp parallel
    {
        // в опции schedule параметр type задаем - dynamic, кол-во итераций = 4
        // итерации цикла распределяются динамически, но размер блока фиксирован
        // каждый поток получает определенное кол-во итераций, и следующую порцию итераций берет тот поток,
        // который первый закончил свою порцию итераций
        #pragma omp for schedule(dynamic, 4)
            for (int i = 0; i < 12; i++) {
                c[i] = a[i] + b[i];
                printf("thread %d, num of threads %d, c[%d] = %d \n", omp_get_thread_num(), omp_get_num_threads(), i, c[i]);
            }

    }

    printf("massive c: ");
    for (int i = 0; i < 12; i ++) {
        printf("%d ", c[i]);
    } printf("\n");

}