/*
Написать программу и запустить ее на p (= 2, 3, 4, 6, 8) процессах.
На нулевом процессе объявить и задать массив из 12 элементов.
С помощью функции MPI_Send разослать блоки массива на остальные процессы.
Размер блока массива (12/p)+1. В результате на нулевом процессе должны быть
элементы массива с 0 до 12/p, на первом процессе с 12/p+1 до 2×(12/p), на 3м процессе
с 2×(12/p)+1 до 3×(12/p) и т.д. Вывести элементы массива на экран на каждом процессе.
Обратите внимание, что не на все процессы хватит элементов.
*/

#include<mpi.h>
#include<stdio.h>
#include<iostream>

using namespace std;
int main(int argc, char **argv)
{
	int current_process, processes;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
	int count_of_elements = 0;

	if (current_process == 0) {
		int a[12] = { 0,1,2,3,4,5,6,7,8,9,10,11 };

		// размер блока
		int size = 12 / processes + 1;
   
		// вывод блока из 0-го процесса
		printf("from process %d: ", current_process);
		for (int i = 0; i < size; i++) {
			printf("%d ", a[i]);
		}
		printf("\n");

		//проход по всем процессам кроме 0-го
		for (int i = 1; i < processes; i++) {

			// начало блока
			int start = i * (12 / processes) + i;

			//проверка последнего блока
			if (12 - start <= size) {
				size = 12 - start;
			}

			MPI_Send(a + start, size < 0 ? 0 : size, MPI_INT, i, 1, MPI_COMM_WORLD);
		}
	}

	else {

		MPI_Probe(MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &count_of_elements);
		int * buffer = new int[count_of_elements];

		MPI_Recv(buffer, count_of_elements, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

		printf("from process %d: ", current_process);
		for (int i = 0; i < count_of_elements; i++) {
			printf("%d ", buffer[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
}