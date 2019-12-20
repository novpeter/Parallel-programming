#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char** argv)
{
   	int x, sum = 0;
   	double time1, time2, duration, global;
   	int size, rank;
    
   	MPI_Init(&argc, &argv);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);
 
   	x = rand();
 
   	time1 = MPI_Wtime();
 
   	MPI_Reduce(&x, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
   	MPI_Bcast(&sum, 1, MPI_INT, 0, MPI_COMM_WORLD);
 
   	time2 = MPI_Wtime();
   	duration = time2 - time1;
   	MPI_Reduce(&duration, &global, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
 
   	if (rank == 0)
        printf("Reduce + Bcast: %f\n", global);
   	
    sum = 0;
 
   	time1 = MPI_Wtime();
 
   	MPI_Allreduce(&x, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
 
   	time2 = MPI_Wtime();
   	duration = time2 - time1;
   	MPI_Reduce(&duration, &global, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
 
   	if (rank == 0)
        printf("Allreduce: %f\n", global);
    
    MPI_Finalize();
}
