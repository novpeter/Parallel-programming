#include<mpi.h>
#include<stdio.h>
#include<iostream>

//using namespace std;
int main(int argc, char **argv)
{
	int current_process, processes;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &processes);

	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

	if (current_process == 1) {
		int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		for (int i = 0; i < processes; i++) {
			if (i != 1) {
				MPI_Send(a, 10, MPI_INT, i, 1, MPI_COMM_WORLD);
			}
		}

	}

	else {
		int count_of_elements;

		MPI_Probe(MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);

		MPI_Get_count(&status, MPI_INT, &count_of_elements);

		int *buffer = new int[count_of_elements];

		MPI_Recv(buffer, count_of_elements, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
		printf("from process %d \n", current_process);
		for (int i = 0; i < count_of_elements; i++) {
			printf("a[%d] = %d ", i, buffer[i]);
		}
	}

	MPI_Finalize();
}
