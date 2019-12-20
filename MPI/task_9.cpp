#include<mpi.h>
#include<stdio.h>
#include<iostream>

using namespace std;

void PingPong(int world_rank, int n)
{
	double startTime = MPI_Wtime();
	if (world_rank == 0) {
		auto x = new int[n];
		for (auto i = 0; i < n; i++) {
			x[i] = i;
		}
		auto returned = new int[n];

		MPI_Send(x, n, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(returned, n, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		auto endTime = MPI_Wtime() - startTime;
		printf("PingPong executed on %d elements in %f\n", n, endTime);
	}
	if (world_rank == 1) {
		auto xBuffer = new int[n];

		MPI_Recv(xBuffer, n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		MPI_Send(xBuffer, n, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
}

void SendPingPing(int n, int world_rank, int sender, int* x, int* returned, double startTime)
{
	MPI_Send(x, n, MPI_INT, sender, 1, MPI_COMM_WORLD);
	MPI_Recv(returned, n, MPI_INT, sender, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	auto endTime = MPI_Wtime() - startTime;
	printf("PingPong executed on %d elements on %d proccess in %f\n", n, world_rank, endTime);
}

void PingPing(int world_rank, int n)
{
	double startTime = MPI_Wtime();
	auto x = new int[n];
	for (auto i = 0; i < n; i++) {
		x[i] = i;
	}
	auto returned = new int[n];

	if (world_rank == 0) {
		SendPingPing(n, world_rank, 1, x, returned, startTime);
	}
	if (world_rank == 1) {
		SendPingPing(n, world_rank, 0, x, returned, startTime);
	}
}

int main(int argc, char** argv)
{
	int world_rank, processes;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	PingPong(world_rank, 1000);

	//PingPing(world_rank, 1000);

	MPI_Finalize();

	return 0;
}