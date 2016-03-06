# French Fries

Let's do a simple example with the following rule:

* A manager processor has an array of size N and is filled with random values.  
* The manager splits up the array into N portions (or subarrays) and sends the subarrays to each of the worker processors.
* Each worker processor would receive its subarray, count up the number of odd elements in the subarray and send the results back to the manager.
* The manager receives the results from all of its workers and print out the total number of odd elements in the array.

## Include files and dependencies

These are header files that tell the compiler what are the functions that are available to our program `french_fries.c`

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>
```

## Variable and Function Definition

These variables are declared at the top of the program but are not shared between MPI processors.

```
int world_size;
int my_rank;
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;
```

These are function definitions that will appear in the program.

```
void doBoss();
void doWorker();
void printArray(int *N, int size);
```

## The main program

The main function makes the determination if the process being executed is a root process (boss) or worker process.

```
int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL); /* initialize the MPI universe */
  MPI_Comm_size(MPI_COMM_WORLD, &world_size); /* get number of processors */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /* get my id */
  MPI_Get_processor_name(processor_name, &name_len); /* get my name */

  // initialize with a random seed base on the process id
  srand((int)getpid());

  // determine if I am the root node (boss)
  if (my_rank == 0) {
    doBoss();
  } else {
    doWorker();
  }

  // call the cleanup function
  MPI_Finalize();

  return 0;
}
```

## Helper functions

This function prints out the contents of the array `N`.  We pass into this function the pointer (memory location) of an integer array and its `size`.

```
void printArray(int *N, int size)
{
  int i = 0;
  printf(" N = [ ");
  for (i = 0; i < size; i++) {
    printf("%d ", N[i]);
  }
  printf("]\n");
}
```

The boss processor's function below does the following:
* Allocate memory `N` of size `N_size`
* Assign a random variable to each of the elements
* Each worker has equal work load if `N_size % worker_count == 0`
* Otherwise workers `1` to `worker_count - 1 ` has one `sub_array_size` and worker `worker_count` has a different partition size
* Sends the sub partition to the workers
* Get back the results from each of the workers and print them

```
void doBoss()
{
  MPI_Status status;

  // reserve memory for array of size N_size
  const int N_size = 20;
  int *N = (int*) malloc(sizeof(int) * N_size);

  // assign random numbers between 1 and 1000 to each element in array
  int i;
  for (i = 0; i < N_size; i++) {
    N[i] = rand() % 1000 + 1;
  }

  // send to total number of workers - 1
  int start, worker_id, worker_count = world_size - 1;

  if (N_size % worker_count == 0) {
    int sub_array_size = N_size/worker_count;
    for (i = 0; i < worker_count; i++) {
      worker_id = i + 1;
      start = i * sub_array_size;
      MPI_Send(&sub_array_size, 1, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
      MPI_Send(&N[start], sub_array_size, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
    }
  } else {
    int sub_array_size = N_size/worker_count;
    for (i = 0; i < worker_count - 1; i++) {
      worker_id = i + 1;
      start = i * sub_array_size;
      MPI_Send(&sub_array_size, 1, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
      MPI_Send(&N[start], sub_array_size, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
    }
    // send to the last one
    worker_id = worker_count;
    start = (worker_id - 1) * sub_array_size;
    int sub_array_size_sm = N_size - (sub_array_size * (worker_count - 1));
    MPI_Send(&sub_array_size_sm, 1, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
    MPI_Send(&N[start], sub_array_size_sm, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
  }

  /* the boss receives from any source */
  int count = world_size;
  int total = 0;

  while (count > 1) {
    int n = 0;
    MPI_Recv(&n, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
    int worker_id = status.MPI_SOURCE;
    printf("Received from worker %02d numberOdds = %d\n", worker_id, n);
    total = total + n;
    count = count - 1;
  }

  printf("Total odd count = %d\n", total);

  free(N); // free up memory -- it's the right thing to do
  return;
}
```

The worker processor's function below does the following:
* Receive size instruction `n`
* Allocate an `array` of size `n`
* Count number of odds in `array`
* Send its result back to the parent

```
void doWorker()
{
  MPI_Status status;
  int master_id = 0;
  int i = 0;
  int n = 0;

  // receive size of array from boss
  MPI_Recv(&n, 1, MPI_INT, master_id, 0, MPI_COMM_WORLD, &status);

  // worker must allocate private array (i.e. where to put data when receiving)
  int *array = (int*) malloc(sizeof(int) * n);

  // receive subarray from boss
  MPI_Recv(array, n, MPI_INT, master_id, 0, MPI_COMM_WORLD, &status);

  // count up the number of odds
  int count = 0;
  for (i = 0; i < n; i++) {
    if (array[i] % 2 == 1) {
      count++;
    }
  }

  /* sleep is implemented here to show that workers completion time varies */
  sleep(rand() % 5);

  // send back to boss odd count see line 91
  MPI_Send(&count, 1, MPI_INT, master_id, 0, MPI_COMM_WORLD);

  free(array); // free up memory -- it's the right thing to do
  return;
}
```
