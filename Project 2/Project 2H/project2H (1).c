#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int *AllocateArray(int N)
{
	int *arr = malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++) {
		arr[i] = rand() % (10 * N + 1);
    }

    return arr;
}

void SortArray(int N, int *A)
{
	int tmp;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (A[j] < A[i]) {
				tmp = A[i];
				A[i] = A[j];
				A[j] = tmp;
            }
        }
    }
}


void DeallocateArray(int *A)
{
	free(A);
}

int main()
{
    int sizes[8] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };

/* For fun:
 *  int sizes[11] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000,
 *                    256000, 512000, 1024000 }; 
 */

    for (int i = 0 ; i < 8 ; i++)
    {
        double alloc_time = 0., sort_time = 0., dealloc_time = 0.;
        struct timeval startTime;
        struct timeval endTime;

	gettimeofday(&startTime, 0);
        int *arr = AllocateArray(sizes[i]);
        gettimeofday(&endTime, 0);
        alloc_time = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;

	gettimeofday(&startTime, 0);
        SortArray(sizes[i], arr);
        gettimeofday(&endTime,0);
        sort_time =(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;

	gettimeofday(&startTime, 0);
        DeallocateArray(arr);
        gettimeofday(&endTime,0);
        dealloc_time = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;

        /* Call the three functions in a sequence. Also use
         * gettimeofday calls surrounding each function and set the 
         * corresponding variable (alloc_time, sort_time, dealloc_time).
         */

        printf("Timings for array of size %d\n", sizes[i]);
        printf("\tTime for allocation is %g, time per element = %g\n", alloc_time, alloc_time/sizes[i]);
        printf("\tTime for sort_time is %g, time per element = %g\n", sort_time, sort_time/sizes[i]);
        printf("\tTime for deallocation is %g\n", dealloc_time);
    }
}
