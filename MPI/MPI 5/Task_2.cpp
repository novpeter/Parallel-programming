#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char** argv)
{
   	int integer;
   	const int n = 4, m = 4;
   	int size, rank;

   	MPI_Status stat;
   	MPI_Init(&argc, &argv);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);

   	int count =  n * m / size;
   	int* b = new int[count];
   	int* scounts = new int[size];
   	int* displs = new int[size];
   	int a[n][m];

   	if (rank == 0)
   	{
         integer += count;
         for(int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                a[i][j] = rand();
            }
         	for (int i = 0; i < size; i++)
         	{
                scounts[i] = count;
                displs[i] = i * count;
         	}
   	}
    
   	MPI_Scatterv(&a, scounts, displs, MPI_INT, b, count, MPI_INT, 0, MPI_COMM_WORLD);
   	MPI_Finalize();
}
