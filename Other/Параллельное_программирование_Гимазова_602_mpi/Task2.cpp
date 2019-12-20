
#include<mpi.h>
#include<iostream>
using namespace std;
int main(int argc, char **argv)
{
	int current_process, processes;
	// èíèöèàëèçàöèÿ ïàðàëëåëüíîé ÷àñòè, îäèí ðàç äëÿ êàæäîãî ïðèëîæåíèÿ
	MPI_Init(&argc, &argv);

	//âîçâðàùàåò ÷èñëî ïðîöåññîâ â êîììóíèêàòîðå
	MPI_Comm_size(MPI_COMM_WORLD, &processes);

	//âîçâðàùàåò íîìåð òåêóùåãî ïðîöåññ â êîììóíèêàòîðå
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);

	cout << " num of process " << current_process;
	cout << " all processes " << processes << endl;

	MPI_Finalize();
}