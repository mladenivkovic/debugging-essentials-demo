#include <stdio.h>
#include <stdlib.h>

#include "include/my_includes.h"

/* Meaningless struct to demo pointer access */
struct my_struct {
  int count;
  double whatever;
  char* text;
};


int main(void) {

  /* Alloc array */
  const int elements = 1000000;
  double* arr = malloc(elements * sizeof(double));

  for (int i = 0; i < elements; i++){

    /* fill up struct with meaningless stuff for demo */
    /* struct is defined in include/my_struct.h */
    struct my_struct st;
    st.count = i;                  /* integer */
    st.whatever = (i % 2) * 23.7;  /* double */
    st.text = "Hello there";       /* char* */

    /* do some stuff */
    /* function is defined in include/my_includes.h */
    do_stuff(&arr[i], i, &st);

    /* print out progress every now and then */
    if (i % 100000 == 0)
      printf("%9d/%9d\n", i, elements);

    /* catch this with breakpoints for demo */
    if (i == 123456 || i == 234567 || i == 345678 || i == 456789)
      printf("Got special i=%9d\n", i);
  }

  /* cleanup */
  free(arr);

  return 0;
}
