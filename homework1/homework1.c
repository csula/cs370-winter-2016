#include <stdio.h>
#include <stdlib.h>


int* createArray(int N, int z)
{
  array = (int*) malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    array[i] = rand() % z;
  }
  return array;
}

void printArray(int *array, int N)
{
  for (int i = 0; i < N; i++) {
    printf("%d %d\n", i, array[i]);
  }
}

int countArray(int *array, int left, int right, int k)
{
  int count = 0;
  for (int i = left; i < right; i++) {
    if (array[i] == k) {
      count++; 
    }
  }
  return count;
}

struct threadArg {
  int* array;
  int id, count, k;
};

void* threadCount(void *arg)
{
  struct threadArg *tArg = (struct threadArg*) arg;
  tArg.count = 0;
  int left = 0; /* you figure it out */
  int right = 0; /* you figure it out */

  tArg.count = countArray(tArg.array, left, right, tArg.k);

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  int N = 0, z = 0, k = 0, M = 0;
  if (argc < 4) {
    printf("usage: %s <N> <z> <k> <M>\n", argv[0]);
    return 0;
  }
  N = atoi(argv[1]);
  z = atoi(argv[2]);
  k = atoi(argv[3]);
  M = atoi(argv[4]);
  printf("N = %d\n", N);
  printf("z = %d\n", z);
  printf("k = %d\n", k);
  printf("M = %d\n", M);

  /* please refer to the thread-demo.c example on creating new threads */
  /* becareful to print *after* all threads are done! */

  return 0;
}
