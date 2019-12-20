/*
Используя блокирующую операцию передачи сообщений (MPI_Send и MPI_Recv) выполнить пересылку данных одномерного массива,
из процесса с номером 1 на остальные процессы группы. На процессах получателях до выставления функции приема (MPI_Recv)
определить количество принятых данных (MPI_Probe). Выделить память под размер приемного буфера, после чего вызвать функцию MPI_Recv.
Полученное сообщение выдать на экран.
*/
#include<mpi.h>
#include<stdio.h>
#include<iostream>

//using namespace std;
int main(int argc, char **argv)
{
	int current_process, processes;
	MPI_Status status;

	// инициализация параллельной части, один раз для каждого приложения
	MPI_Init(&argc, &argv);
	//возвращает число процессов в коммуникаторе
	MPI_Comm_size(MPI_COMM_WORLD, &processes);
	//возвращает номер текущего процесс в коммуникаторе
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

	if (current_process == 1) {
		int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		// отправка сообщения
		for (int i = 0; i < processes; i++) {
			if (i != 1) {
				MPI_Send(a, 10, MPI_INT, i, 1, MPI_COMM_WORLD);
			}
		}

	}

	else {
		int count_of_elements;

		/* MPI_Probe вернет управление, когда сообщение будет уже на приемной стороне в служебном буфере */
		MPI_Probe(MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);

		MPI_Get_count(&status, MPI_INT, &count_of_elements);

		/* Принятое будет размещено в динамической памяти:
		 * заказываем в ней буфер соответствующей длины
		 */

		int *buffer = new int[count_of_elements];

		/* MPI_Recv просто скопирует уже принятые данные из системного буфера в пользовательский*/
		MPI_Recv(buffer, count_of_elements, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
		printf("from process %d \n", current_process);
		for (int i = 0; i < count_of_elements; i++) {
			printf("a[%d] = %d ", i, buffer[i]);
		}
	}

	MPI_Finalize();
}