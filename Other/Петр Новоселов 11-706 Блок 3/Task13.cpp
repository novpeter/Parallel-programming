#include<mpi.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	int current_process, processes;
	MPI_Comm_size(MPI_COMM_WORLD, &processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

	const int n = 4;

	int countOfPart = 0;
	int localsum = 0;
	int globalMax = 0;
	int sendCount = 4;
	int getCount = sendCount;

	int arrayA[n][n] = 
	{
		{1,2,-3,1},
		{0,-2,-3,2},
		{1,0,3,-3},
		{-1,-2,1,4}
	};

	int arrayB[n][n] =
	{
		{2,2,2,2},
		{1,1,1,1},
		{0,0,0,0},
		{3,3,3,3}
	};

	int getbufA[n];
	int getbufB[n];	
	
	int arrayC[n][n];
	int bufC[n];
	
	MPI_Scatter(arrayA, n, MPI_INT, getbufA, n, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(arrayB, n, MPI_INT, getbufB, n, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < n; i++) {
		bufC[i] = getbufA[i] * getbufB[i];
	}
	
	MPI_Gather(bufC, n, MPI_INT, arrayC, n, MPI_INT, 0, MPI_COMM_WORLD);
	
	if (current_process == 0) {
		printf("MATRIX C \n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", arrayC[i][j]);
			}
			printf("\n");
		}
	}

	MPI_Finalize();
}