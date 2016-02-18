#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SEED 1024

struct DataValue {
  int value, count, start, end;
  int* array;
};

void printDataValue(struct DataValue *dv)
{
  printf("--\n");
  printf("value = %d\n", dv->value);
  printf("count = %d\n", dv->count);
  printf("start = %d\n", dv->start);
  printf("end = %d\n", dv->end);
}

void* count_number(void* input ) {
    struct DataValue* data = (struct DataValue*) input;
    int value = data->value;
    int count = 0;
    int start = data->start;
    int end = data->end;
    int* array = data->array;

    for (int i = start; i < end; i++) {
      if (array[i] == value) {
        ++count;
      }
    }

    data->count = count;

    return NULL;
}

int
main(int argc, char *argv[])
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
  
  int array[N];
  
  srand(SEED);
  for (int i = 0; i < N; i++) {
    array[i] = rand() % z;
    printf("a[%d] = %d\n", i, array[i]);
  }
  
  struct DataValue data[M];
  pthread_t threads[M];
  int rc = 0;
  int t = 0;
  int total = 0;
  
  int taskPerThread = (N+M-1)/M;
  
  printf("taskPerThread = %d\n", taskPerThread);

  for (t = 0; t < M; t++) {
    data[t].value = k;
    data[t].start = t * taskPerThread;
    data[t].end = (t + 1) * taskPerThread;
    data[t].array = &array[0];
  }
  
  data[M-1].end = N;

  for (t = 0; t < M; t++) {
    struct DataValue *dv = &data[t];
    printDataValue(dv);
    rc = pthread_create(&threads[t], NULL, count_number, (void*)dv);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  
  for (t = 0; t < M; t++) {
    pthread_join(threads[t], NULL);
  }
  
  for (t = 0; t < M; t++) {
    int count = data[t].count;
    printf("t(%d) = %d \n", t, count);
    total += count;
  }

  printf("Total = %d\n", total);
  pthread_exit(NULL);
  
  return 0;
}

