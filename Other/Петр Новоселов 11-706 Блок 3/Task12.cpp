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

	int array[n][n] = 
	{
		{1,2,-3,1},
		{0,-2,-3,2},
		{1,0,3,-3},
		{-1,-2,1,4}
	};

	int sendbuf[n][n];
	int getbuf[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sendbuf[i][j] = array[j][i];
			printf("%d ", sendbuf[i][j]);
		}
		printf("\n");
	}
	
	
	MPI_Scatter(sendbuf, n, MPI_INT, getbuf, n, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < n; i++) {
		localsum += abs(getbuf[i]);
	}

	printf("process = %d, localsum = %d \n", current_process, localsum);

	MPI_Reduce(&localsum, &globalMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	
	if (current_process == 0) {
		printf("max = %d \n", globalMax);
	}

	MPI_Finalize();
}