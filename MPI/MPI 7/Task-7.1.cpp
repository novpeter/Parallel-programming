#include<mpi.h>
#include<iostream>
#include<math.h>

int main(int argc, char** argv)
{
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Group worldGroup, newGroup;

	MPI_Comm newComm;

	int groupSize = 5;
	int ranks[5] = { 8, 3, 9, 1, 6 };
	int rank_in_group = -1;
	const int n = 30;

	MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);
	MPI_Group_incl(worldGroup, groupSize, ranks, &newGroup);
	MPI_Comm_create(MPI_COMM_WORLD, newGroup, &newComm);

	if (newComm != MPI_COMM_NULL) {
		MPI_Comm_rank(newComm, &rank_in_group);
	}

	if (rank_in_group >= 0) {
		double a[n];
		
		if (rank_in_group == 0) {
			printf("array a: \n");
			for (int i = 0; i < n; i++) {
				a[i] = rand() % 10;
				printf("%.2f ", a[i]);
			}
			printf("\n");
		}


		MPI_Bcast(&a, n, MPI_DOUBLE, 0, newComm);
		for (int i = 0; i < n; i++) {
			printf("%.2f ", a[i]);
		}
		printf("\n\n");


		if (groupSize - 1 == rank_in_group) {
			printf("Send \n");
			MPI_Send(a, n, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
		}

	}

	// на общем коммуникаторе
	if (rank == 0) {
		double array[n];
		printf("aa");
		MPI_Status status;
		MPI_Recv(array, n, MPI_DOUBLE, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
		for (int i = 0; i < n; i++) {
			printf("Rank: %d %.2f ", rank, array[i]);
		}
		printf("\n");
	}

	MPI_Group_free(&worldGroup);
	MPI_Group_free(&newGroup);

	MPI_Finalize();
}
