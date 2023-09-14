#include <stdio.h>
#include <stdlib.h>

#include "include/my_includes.h"
#include "include/my_struct.h"


int main(void) {

  /* Alloc array */
  const int elements = 1000000;
  double* arr = malloc(elements * sizeof(double));

  for (int i = 0; i < elements; i++){

    /* fill up struct with meaningless stuff for demo */
    struct my_struct st;
    st.count = i;                  /* integer */
    st.whatever = (i % 2) * 23.;   /* double */
    st.text = "Hello there";       /* char* */

    /* do some stuff */
    do_stuff(&arr[i], i, &st);

    /* print out progress every now and then */
    if (i % 100000 == 0)
      printf("%9d/%9d\n", i, elements);
  }

  /* cleanup */
  free(arr);

  return 0;
}
