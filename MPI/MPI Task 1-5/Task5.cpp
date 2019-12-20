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
		int size = 12 / processes + 1;
   
		printf("from process %d: ", current_process);
		for (int i = 0; i < size; i++) {
			printf("%d ", a[i]);
		}
		printf("\n");

		for (int i = 1; i < processes; i++) {
			int start = i * (12 / processes) + i;

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
