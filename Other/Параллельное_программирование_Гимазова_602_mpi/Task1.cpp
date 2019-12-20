//�������� mpi ���������, ���������� "Hello, World!". ��������� ��������� �� 4 ���������.  

#include<mpi.h>
#include<iostream>
using namespace std;
int main(int argc, char **argv)
{
	int current_process, processes;
	// ������������� ������������ �����, ���� ��� ��� ������� ����������
	MPI_Init(&argc, &argv);

	//���������� ����� ��������� � �������������
	MPI_Comm_size(MPI_COMM_WORLD, &processes);

	//���������� ����� �������� ������� � �������������
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

	cout << "Hello world! from process " << current_process;
	cout << " of " << processes << endl;
	MPI_Finalize();
}