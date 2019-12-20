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

	int n = 11;

	if (current_process == 0) {
		int x[11] = { 0,1,2,3,4,5,6,7,8,9,10 };
		int y[11] = { 4,5,6,7,8,9,0,1,2,3,5 };

		int size = ceil((double) n / (processes - 1));

		for (int i = 1; i < processes; i++) {

			int start = (i - 1) * size;

            if (n - start <= size) {
				size = n - start;
			}

			MPI_Send(x + start, size < 0 ? 0 : size, MPI_INT, i, 11, MPI_COMM_WORLD);
			MPI_Send(y + start, size < 0 ? 0 : size, MPI_INT, i, 22, MPI_COMM_WORLD);
		}

		for (int i = 1; i < processes; i++) {
			MPI_Status status_z;
			int elements_z = 0;
			int * buffer_z;

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

        MPI_Probe(MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &status_x);
		MPI_Get_count(&status_x, MPI_INT, &elements_x);
		buffer_x = new int[elements_x];
		MPI_Recv(buffer_x, elements_x, MPI_INT, MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &status_x);

		MPI_Probe(MPI_ANY_SOURCE, 22, MPI_COMM_WORLD, &status_y);
		MPI_Get_count(&status_y, MPI_INT, &elements_y);
		buffer_y = new int[elements_y];
		MPI_Recv(buffer_y, elements_y, MPI_INT, MPI_ANY_SOURCE, 22, MPI_COMM_WORLD, &status_y);

		printf("process %d: \n", current_process);

		for (int i = 0; i < elements_x; i++) {
			printf(" x : %d ", buffer_x[i]);
		}
		printf("\n");

		for (int i = 0; i < elements_x; i++) {
			printf(" y : %d ", buffer_y[i]);
		}
		printf("\n");

		int *z = new int[elements_x];
		for (int i = 0; i < elements_x; i++) {
			z[i] = buffer_x[i] * buffer_y[i];
			printf(" z : %d ", z[i]);
		}
		printf("\n\n");

		MPI_Send(z, elements_x, MPI_INT, 0, 33, MPI_COMM_WORLD);
	}
	
    MPI_Finalize();
}
