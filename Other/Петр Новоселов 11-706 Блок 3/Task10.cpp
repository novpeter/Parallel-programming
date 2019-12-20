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

	int countOfPart = 0;
	int localsum = 0;
	int globalsum = 0;
	const int n = 20;

	countOfPart = n / processes;
	int * sendbuf = new int[n];
	int * getbuf = new int[countOfPart];

	for (int i = 0; i < 20; i++) {
		sendbuf[i] = i + 1;
	};

	MPI_Scatter(sendbuf, countOfPart, MPI_INT, getbuf, countOfPart, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < countOfPart; i++) {
		localsum += abs(getbuf[i]);
	}

	printf("localsum = %d \n", localsum);
	
	MPI_Reduce(&localsum, &globalsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (current_process == 0) {
		printf("global sum = %d \n", globalsum);
	}

	MPI_Finalize();
}