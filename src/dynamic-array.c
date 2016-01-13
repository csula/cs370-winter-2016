#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  int N = 0, z = 0;
  int *array = NULL;

  if (argc < 2) {
    printf("usage: %s <N> <z>\n", argv[0]);
    return 0;
  }
  N = atoi(argv[1]);
  z = atoi(argv[2]);
  printf("N = %d\n", N);
  printf("z = %d\n", z);

  array = (int*) malloc(z * sizeof(int));
  for (int i = 0; i < N; i++) {
    array[i] = rand() % z;
  }
  for (int i = 0; i < N; i++) {
    printf("%d %d\n", i, array[i]);
  }
}
