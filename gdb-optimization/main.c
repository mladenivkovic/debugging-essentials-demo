#include <stdio.h>
#include <stdlib.h>

/**
 * Initialize array of size `elements` with some values.
 * While doing that, produce a segfault by writing
 * outside of array boundaries. */
/* #pragma GCC push_options */
/* #pragma GCC optimize ("O0") */
void assign_array_values(int *arr, const int elements){

  /* Loop over array indices which haven't been allocated
   * to produce a segfault */
  for (int i = 0; i < 2 * elements; i++){

    arr[i] = i;

    if (i % 100000 == 0)
      printf("%4d/%d\n", i, elements);

  }
}
/* #pragma GCC pop_options */



int main(void) {

  const int elements = 10000000;

  /* allocate some array */
  int *arr = malloc(elements * sizeof(int));

  /* fill it up with data and cause segfault */
  assign_array_values(arr, elements);

  return 0;
}











/* #pragma GCC push_options */
/* #pragma GCC optimize ("O0") */
/*  */
/* your code */
/*  */
/* #pragma GCC pop_options */
