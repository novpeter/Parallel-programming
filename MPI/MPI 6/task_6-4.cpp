#include<mpi.h>
#include<iostream>
#include<math.h>

using namespace std;

struct TwoArraysStruct
{
	int firstLine[10];
	double secondLine[8];
};

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);
	int world_rank, processes;
	MPI_Comm_size(MPI_COMM_WORLD, &processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	struct TwoArraysStruct linesType;
	int blockLengths[2] = { 10, 8 };

	MPI_Datatype types[2] = { MPI_INT, MPI_DOUBLE };
	MPI_Aint adr[2];

	adr[0] = offsetof(struct TwoArraysStruct, firstLine);
	adr[1] = offsetof(struct TwoArraysStruct, secondLine);

	MPI_Datatype newType;

	MPI_Type_create_struct(2, blockLengths, adr, types, &newType);
	MPI_Type_commit(&newType);

	if (world_rank == 0) {
		printf("Sending: \n");
		for (int i = 0; i < 10; i++) {
			linesType.firstLine[i] = i;
			printf("%d ", linesType.firstLine[i]);
		}
		printf("\n");
		for (int i = 0; i < 8; i++) {
			linesType.secondLine[i] = i;
			printf("%.1f ", linesType.secondLine[i]);
		}
		printf("\n");
		for (int i = 1; i < processes; i++)
			MPI_Send(&linesType, 1, newType, i, 1, MPI_COMM_WORLD);
	}
	else {
		MPI_Status status;

		MPI_Recv(&linesType, 1, newType, 0, 1, MPI_COMM_WORLD, &status);

		printf("on %d: \n", world_rank);
		for (int j = 0; j < 10; j++) {
			printf("%d ", linesType.firstLine[j]);
		}
		printf("\n");

		for (int j = 0; j < 8; j++) {
			printf("%.1f ", linesType.secondLine[j]);
		}
		printf("\n");
	}

	MPI_Finalize();

	return 0;
}