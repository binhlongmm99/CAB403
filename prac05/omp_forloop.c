#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	omp_set_num_threads(4);
	int val[8];

	// Modifiers to the construct - shared specifies the listed variables should
	// be shared by all threads.
	#pragma omp parallel default(none) shared(val)
	{
		//we'll use our 4 threads to calculate & store the cubes of 1 - 9
		#pragma omp for
		for (int i = 1; i < 9; ++i)
		{
			val[i - 1] = i * i * i;
			int thread = omp_get_thread_num();

			printf("%d^3=%d, using thread %d\n", i, val[i - 1], thread);
		}
	}
}
