#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <mpi.h>

static const int TRUE  = 1;
static const int FALSE = 0;

static int world_size;
static int world_rank;
static int name_len;
static char processor_name[MPI_MAX_PROCESSOR_NAME];

#define A(u, n, y, x) (u[(y) * (n) + (x)])

int* createArray(int N, int z)
{
  int *array = (int*) malloc(N * sizeof(int));
	int i = 0;

  for (i = 0; i < N; i++) {
    array[i] = rand() % z;
  }
  return array;
}

void printArray(int *array, int n)
{
	int i = 0, j = 0;

  printf("---\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%02d ", A(array, n, i, j));
		}
		printf("\n");
	}
  printf("---\n");
}

double calcSum(int *array, int N)
{
	int i = 0;
	double sum = 0.0;
	for (i = 0; i < N; i++) {
		sum += array[i];
	}

	return sum;
}

double calcMean(int *array, int N)
{
	return calcSum(array, N)/N;
}

double calcStd(int *array, int N)
{
	int i = 0;
	double ss = 0.0, mean = calcMean(array, N);

	for (i = 0; i < N; i++) {
		ss += (mean - array[i]) * (mean - array[i]);
	}

	return sqrt(ss/N);
}

double findMax(int *array, int N)
{
	double max = (double) LONG_MIN;
	int i = 0;
	for (i = 0; i < N; i++) {
		max = (max > array[i] ? max : array[i]);
	}

	return max;
}

double findMin(int *array, int N)
{
	double min = (double) LONG_MAX;
	int i = 0;
	for (i = 0; i < N; i++) {
		min = (min < array[i] ? min : array[i]);
	}

	return min;
}

int getArguments(int argc, char* argv[], int *n, int *z, int *seed)
{
	if (argc < 3) {
    printf("usage: %s <n> <z> <seed>\n", argv[0]);
		return FALSE;
  }

  *n = atoi(argv[1]);
  *z = atoi(argv[2]);
  *seed = atoi(argv[3]);

	return TRUE;
}

void doManager(int n, int z, int seed)
{
	int N = n * n;
	int *matrix = createArray(N, z);

	printf("[%s.%d] manager started\n", processor_name, world_rank);
	// begin parallel code; fill in the missing code here
	double mean = 0.0, std = 0.0, max = 0.0, min = 0.0;

  // end parallel code; no more code change required
	printf("[%s.%d] manager completed\n", processor_name, world_rank);

	sleep(1);
	printArray(matrix, n);
	printf("N    = %d\n", N);
	printf("sum  = %g %g\n", std, calcSum(matrix, N));
	printf("mean = %g %g\n", mean, calcMean(matrix, N));
	printf("std  = %g %g\n", std, calcStd(matrix, N));
	printf("max  = %g %g\n", max, findMax(matrix, N));
	printf("min  = %g %g\n", min, findMin(matrix, N));
}

void doWorker()
{
	printf("[%s.%d] worker started\n", processor_name, world_rank);
	// begin parallel code; fill in the missing code here

  // end parallel code; no more code change required
	printf("[%s.%d] worker completed\n", processor_name, world_rank);
}

int main(int argc, char** argv)
{
  // MPI_Status status;
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // Get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Get_processor_name(processor_name, &name_len);

	int proceed_flag = 0;
	int n = 0;
	int z = 0;
	int seed = 0;

	if (world_rank == 0) {
		proceed_flag = getArguments(argc, argv, &n, &z, &seed);
	}

	// broadcast instruction
	MPI_Bcast(&proceed_flag, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (proceed_flag == TRUE) {
		if (world_rank == 0) {
			doManager(n, z, seed);
		} else {
			doWorker();
		}
	}

	printf("[%s.%d] program completed\n", processor_name, world_rank);

  // Finalize the MPI environment.
  MPI_Finalize();

  return 0;
}
