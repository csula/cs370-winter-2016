#include <stdio.h>
#include <stdlib.h>

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

  return 0;
}
