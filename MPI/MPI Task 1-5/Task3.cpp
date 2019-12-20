#include<mpi.h>
#include<iostream>
#include<stdio.h>
#include<math.h>

int main(int argc, char **argv)
{
	int current_process, processes;
	MPI_Status status;

    MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &processes);

	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

	if (current_process == 0) {
		int a[10];
		printf("array from %d: \n", current_process);

		for (int i = 0; i < 10; i++) {
			a[i] = 1 + rand() % 10;
			printf(" %d ", a[i]);
		};
		printf("\n");

        MPI_Send(a, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}

	else if (current_process == 1)
	{
		int count_of_elements;

		MPI_Probe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		
        MPI_Get_count(&status, MPI_INT, &count_of_elements);
		
        int *buffer = new int[count_of_elements];

		MPI_Recv(buffer, count_of_elements, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        
		printf("array from %d: \n", current_process);
		for (int i = 0; i < 10; i++)
		{
			printf(" %d ", buffer[i]);
		}
		printf("\n");
	}

	MPI_Finalize();
}
