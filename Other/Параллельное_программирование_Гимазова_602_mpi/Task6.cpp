/*
Написать программу, вычисляющую элементы вектора z  по формуле zi= a*xi+b*yi.
Векторы х, у задаются на нулевом процессе и равными блоками пересылаются
остальным процессам, a,b - заданные числа. Пересылка данных осуществляется
функцией MPI_Send. Все процессы по формуле вычисляют свои элементы массива z.
Каждый процесс отправляет на нулевой процесс подсчитанные элементы.
*/

#include<mpi.h>
#include<stdio.h>
#include<iostream>

using namespace std;
int main(int argc, char **argv)
{
	int current_process, processes;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

	// для вычисления вектора z
	int a = 1;
	int b = 2;

	int n = 11;

	if (current_process == 0) {
		int x[11] = { 0,1,2,3,4,5,6,7,8,9,10 };
		int y[11] = { 4,5,6,7,8,9,0,1,2,3,5 };

		// размер блока, вычитаем нулевой процесс и округляем в бОльшую сторону
		int size = ceil((double)n / (processes - 1));

		//проход по всем процессам кроме 0-го
		for (int i = 1; i < processes; i++) {

			// начало блока 
			int start = (i - 1) * size;

			//проверка последнего блока
			if (n - start <= size) {
				size = n - start;
			}

			// отправка векторов х и у, х отправляем с тегом 11, у - с тегом 22
			MPI_Send(x + start, size < 0 ? 0 : size, MPI_INT, i, 11, MPI_COMM_WORLD);
			MPI_Send(y + start, size < 0 ? 0 : size, MPI_INT, i, 22, MPI_COMM_WORLD);
		}

		// получаем и печатаем вектор z, полученный по блокам из потоков (кроме нулевого)
		for (int i = 1; i < processes; i++) {
			MPI_Status status_z;
			int elements_z = 0;
			int * buffer_z;

			// получаем сообщение по тегу 33
			MPI_Probe(i, 33, MPI_COMM_WORLD, &status_z);
			MPI_Get_count(&status_z, MPI_INT, &elements_z);
			buffer_z = new int[elements_z];
			MPI_Recv(buffer_z, elements_z, MPI_INT, i, 33, MPI_COMM_WORLD, &status_z);

			printf("process %d, part of vector z from process %d: \n", current_process, i);

			for (int i = 0; i < elements_z; i++) {
				printf("%d ", buffer_z[i]);
			}
			printf("\n\n");
		}
	}

	else {
		int elements_x = 0;
		int elements_y = 0;
		int * buffer_x;
		int * buffer_y;

		MPI_Status status_x;
		MPI_Status status_y;

		// получаем вектор x через тег 11, размер блока записывается в переменную elements_x
		MPI_Probe(MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &status_x);
		MPI_Get_count(&status_x, MPI_INT, &elements_x);
		buffer_x = new int[elements_x];
		MPI_Recv(buffer_x, elements_x, MPI_INT, MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &status_x);

		// получаем вектро у через тег 22, размер блока записывается в переменную elements_y
		MPI_Probe(MPI_ANY_SOURCE, 22, MPI_COMM_WORLD, &status_y);
		MPI_Get_count(&status_y, MPI_INT, &elements_y);
		buffer_y = new int[elements_y];
		MPI_Recv(buffer_y, elements_y, MPI_INT, MPI_ANY_SOURCE, 22, MPI_COMM_WORLD, &status_y);

		printf("process %d: \n", current_process);

		// печатаем вектор х

		for (int i = 0; i < elements_x; i++) {
			printf(" x : %d ", buffer_x[i]);
		}
		printf("\n");

		// печатаем вектор у
		for (int i = 0; i < elements_x; i++) {
			printf(" y : %d ", buffer_y[i]);
		}
		printf("\n");

		//вычисляем и печатаем вектор z
		int *z = new int[elements_x];
		for (int i = 0; i < elements_x; i++) {
			z[i] = a * buffer_x[i] + b * buffer_y[i];
			printf(" z : %d ", z[i]);
		}
		printf("\n\n");

		// передаем процессу 0 вычисленный вектор z под тегом 33
		MPI_Send(z, elements_x, MPI_INT, 0, 33, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}