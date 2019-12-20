//Написать mpi программу, печатающую "Hello, World!". Запустить программу на 4 процессах.  

#include<mpi.h>
#include<iostream>
using namespace std;
int main(int argc, char **argv)
{
	int current_process, processes;
	// инициализация параллельной части, один раз для каждого приложения
	MPI_Init(&argc, &argv);

	//возвращает число процессов в коммуникаторе
	MPI_Comm_size(MPI_COMM_WORLD, &processes);

	//возвращает номер текущего процесс в коммуникаторе
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

	cout << "Hello world! from process " << current_process;
	cout << " of " << processes << endl;
	MPI_Finalize();
}