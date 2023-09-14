#include <stdio.h>
#include <stdlib.h>

int main(void) {

  const int elements = 10000000;

  /* allocate some array */
  int *arr = malloc(elements * sizeof(int));

  /* Loop over array indices which haven't been allocated
   * to produce a segfault */
  for (int i = 0; i < 2 * elements; i++){

    arr[i] = i;

    if (i % 100000 == 0)
      printf("%4d/%d\n", i, elements);

  }

  return 0;
}
