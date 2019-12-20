#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	printf("Way 1\n");
#pragma omp parallel num_threads(8)
	{
		int threadsCount = omp_get_num_threads();
		for (int i = threadsCount - 1; i >= 0; i--)
		{
#pragma omp barrier
			if (i == omp_get_thread_num())
#pragma omp critical
				printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
		}
	}

	printf("Way 2\n");
	int counter = 7;
#pragma omp parallel num_threads(8)
	{
		while (counter != omp_get_thread_num()) {}
		printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
#pragma omp atomic
		counter--;
	}
	

	printf("Way 3\n");
	int count = 7;
	while (count >= 0)
	{
#pragma omp parallel num_threads(8)
		{
			if (count == omp_get_thread_num())
			{
				printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
#pragma omp atomic
				count--;
			}
		}
	}
	

	printf("Way 4\n");
	int threads[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int numberThreads = 0;
#pragma omp parallel num_threads(8)
	{
		numberThreads = omp_get_num_threads();
#pragma omp for
		for (int i = 0; i < numberThreads; i++)
			threads[i] = omp_get_thread_num();
	}

	for (int i = 7; i >= 0; i--)
		printf("Hello World! Thread: %d All:%d\n", threads[i], numberThreads);


	printf("Way 5\n");
#pragma omp parallel num_threads(8)
	{
		if (omp_get_thread_num() == 7)
		{
			printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier
		if (omp_get_thread_num() == 6)
		{
			printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier
		if (omp_get_thread_num() == 5)
		{
			printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier
		if (omp_get_thread_num() == 4)
		{
			printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier
		if (omp_get_thread_num() == 3)
		{
			printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier
		if (omp_get_thread_num() == 2)
		{
			printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier
		if (omp_get_thread_num() == 1)
		{
			printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier
		if (omp_get_thread_num() == 0)
		{
			printf("Hello World! Thread: %d All:%d\n", omp_get_thread_num(), omp_get_num_threads());
		}
	}
}