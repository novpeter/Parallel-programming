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
	int local = 0;
	int sendCount = 4;
	int getCount = sendCount;

	int array[n][n] =
	{
		{1,2,-3,1},
		{0,-2,-3,2},
		{1,0,3,-3},
		{-1,-2,1,4}
	};

	int x[n] = { 2,2,2,2 };
	int z[n];
	int getbuf[n];

	MPI_Scatter(array, n, MPI_INT, getbuf, n, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(x, n, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < n; i++) {
		local += getbuf[i] * x[i];
	}

	printf("localVal = %d from process %d \n", local, current_process);

	MPI_Gather(&local, 1, MPI_INT, z, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (current_process == 0) {
		printf("Z = ");
		for (int i = 0; i < n; i++) {
			printf("%d ", z[i]);
		}
		printf("\n");
	}

	MPI_Finalize();
}