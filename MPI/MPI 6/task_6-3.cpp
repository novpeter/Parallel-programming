#include<mpi.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;

void printArray(int n, int m, int a[8][8]) 
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%.2d ", a[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);
	int world_rank, processes;
	MPI_Comm_size(MPI_COMM_WORLD, &processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	const int n = 8;
	const int m = 8;

	int a[n][m] =
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	};

	MPI_Datatype newType;
	int blockLens[n] = { 8,7,6,5,4,3,2,1 };
	int indices[n] = { 1,5,14,23,31,40,55,60 };

	// Конструктор
	MPI_Type_indexed(n, blockLens, indices, MPI_INT, &newType);
	MPI_Type_commit(&newType);

	if (world_rank == 0) {
		int counter = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = counter;
				counter++;
			}
		}

		printf("Original matrix: \n");
		printArray(n, m, a);
	}

	// рассылка информации от одного процесса всем остальным членам некоторой области связи
	MPI_Bcast(&a, 1, newType, 0, MPI_COMM_WORLD);

	if (world_rank == 1) {
		printf("Received matrix: \n");
		printArray(n, m, a);
	}

	MPI_Finalize();

	return 0;
}
