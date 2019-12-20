#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char** argv)
{
   	int size, rank;
   	int ranks1[6] = { 0, 2, 4, 6, 5, 7 };
 
   	MPI_Comm comm1, comm2, comm3, comm4, local, icomm, icomm1, dup_comm_world;
   	MPI_Group group1, group2, group3, group4, wgroup;
 
   	MPI_Init(&argc, &argv);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
   	MPI_Comm_group(MPI_COMM_WORLD, &wgroup);
   	MPI_Group_incl(wgroup, 6, ranks1, &group1);
   	MPI_Group_excl(wgroup, 6, ranks1, &group2);
 
   	MPI_Group_incl(wgroup, 6, ranks1, &group3);
   	MPI_Group_excl(wgroup, 6, ranks1, &group4);
 
	// создаем 4 группы
   	MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
   	MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);
   	MPI_Comm_create(MPI_COMM_WORLD, group3, &comm3);
   	MPI_Comm_create(MPI_COMM_WORLD, group4, &comm4);
 
   	int rank1 = -1;
   	int rank2 = -1;
   	int rank3 = -1;
   	int rank4 = -1;

   	if (comm1 != MPI_COMM_NULL)
         	MPI_Comm_rank(comm1, &rank1);
   	if (comm2 != MPI_COMM_NULL)
         	MPI_Comm_rank(comm2, &rank2);
   	if (comm3 != MPI_COMM_NULL)
         	MPI_Comm_rank(comm3, &rank3);
   	if (comm4 != MPI_COMM_NULL)
         	MPI_Comm_rank(comm4, &rank4);
 
    const int n = 5;
   	char nameout[MPI_MAX_OBJECT_NAME];
   	int rlen;
   	int globalres[n * 6];
   	int tag = 777;
   	int rlead;
    

    // создаем интеркоммуникаторы для обмена информацией между группами
   	if (comm1 != MPI_COMM_NULL)
   	{
            local = comm1;
            rlead = 1;
            MPI_Intercomm_create(local, 0, MPI_COMM_WORLD, rlead, tag, &icomm);
   	}
    
   	if (comm2 != MPI_COMM_NULL)
   	{
            local = comm2;
            rlead = 0;
            MPI_Intercomm_create(local, 0, MPI_COMM_WORLD, rlead, tag, &icomm);
   	}
 
   	if (comm3 != MPI_COMM_NULL)
   	{
         	tag = 888;
         	local = comm3;
         	rlead = 3;
         	MPI_Intercomm_create(local, 1, MPI_COMM_WORLD, rlead, tag, &icomm1);
   	}
    
   	if (comm4 != MPI_COMM_NULL)
   	{
         	tag = 888;
         	local = comm4;
         	rlead = 2;
         	MPI_Intercomm_create(local, 1, MPI_COMM_WORLD, rlead, tag, &icomm1);
   	}
 

   	if (rank1 >= 0)
   	{
         	int a[n];
         	for (int i = 0; i < n; i++)
                	a[i] = 1;
 
         	MPI_Gather(&a, n, MPI_INT, &globalres[0], n, MPI_INT, 0, comm1);
         	if (rank1 == 0)
         	{
                	printf("Group 1\n");
                	for (int i = 0; i < n * 6; i++)
                       	printf("%d ", globalres[i]);
                	printf("%\n"); // печатаю на 0 ранге
                	MPI_Send(&globalres, n * 6, MPI_INT, 0, 12, icomm); //отправляю в интеркоммуникатор
         	}
   	}
 
   	if (rank2 >= 0)
   	{
         	int a[n];
         	for (int i = 0; i < n; i++)
                	a[i] = 2;
 
         	MPI_Gather(&a, n, MPI_INT, &globalres[0], n, MPI_INT, 0, comm2);
         	if (rank2 == 0)
         	{
                	printf("Group 2\n");
                	for (int i = 0; i < n * 6; i++)
                       	printf("%d ", globalres[i]);
                	printf("\n");
 
                	printf("I'm from group 2 recv array from group 1\n");
                	int recArr[n * 6];
                	MPI_Recv(&recArr[0], n * 6, MPI_INT, MPI_ANY_SOURCE, 12, icomm, MPI_STATUSES_IGNORE);
                	for (int i = 0; i < n * 6; i++)
                       	printf("%d ", recArr[i]);
                	printf("\n");
 
                	MPI_Send(&globalres, n * 6, MPI_INT, 0, 12, icomm);
         	}
   	}

   	if (rank1 == 0)
   	{
			// получил со 2 группы массив
         	printf("I'm from group 1 recv array from group 2\n");
         	int recArr[n * 6];
         	MPI_Recv(&recArr[0], n * 6, MPI_INT, MPI_ANY_SOURCE, 12, icomm, MPI_STATUSES_IGNORE);
         	for (int i = 0; i < n * 6; i++)
                	printf("%d ", recArr[i]);
         	printf("\n");
   	}
 
   	if (rank3 >= 0)
   	{
         	int a[n];
         	for (int i = 0; i < n; i++)
         	   	a[i] = 3;
 
         	MPI_Gather(&a, n, MPI_INT, &globalres[0], n, MPI_INT, 0, comm3);
         	if (rank3 == 0)
         	{
                	printf("Group 3\n");
                	for (int i = 0; i < n * 6; i++)
                       	printf("%d ", globalres[i]);
                	printf("%\n");
                	MPI_Send(&globalres, n * 6, MPI_INT, 0, 12, icomm1);
         	}
 
   	}
 
   	if (rank4 >= 0)
   	{
         	int a[n];
         	for (int i = 0; i < n; i++)
                	a[i] = 4;
 
         	MPI_Gather(&a, n, MPI_INT, &globalres[0], n, MPI_INT, 0, comm4);
 
         	if (rank4 == 0)
         	{
                	printf("Group 4\n");
                	for (int i = 0; i < n * 6; i++)
                       	printf("%d ", globalres[i]);
                	printf("%\n");
 
                	printf("I'm from group 4 recv array from group 3\n");
                	int recArr[n * 6];
                	MPI_Recv(&recArr[0], n * 6, MPI_INT, MPI_ANY_SOURCE, 12, icomm1, MPI_STATUSES_IGNORE);
                	for (int i = 0; i < n * 6; i++)
                       	printf("%d ", recArr[i]);
                	printf("\n");
 
                	MPI_Send(&globalres, n * 6, MPI_INT, 0, 12, icomm1);
         	}
   	}
 
   	if (rank3 == 0)
   	{
			// получил с 4 
         	printf("I'm from group 3 recv array from group 4\n");
         	int recArr[n * 6];
         	MPI_Recv(&recArr[0], n * 6, MPI_INT, MPI_ANY_SOURCE, 12, icomm1, MPI_STATUSES_IGNORE);
         	for (int i = 0; i < n * 6; i++)
                	printf("%d ", recArr[i]);
         	printf("\n");
   	}
 
   	MPI_Finalize();
}
