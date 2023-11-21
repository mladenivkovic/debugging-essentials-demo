/* To use feenableexcept() with gcc, you need to define the macro below first.
 * The function `feenableexcept()` is not standard C, but a GNU extension. */
/* #define _GNU_SOURCE */
/* #include <fenv.h> [> Make sure to link with -lm as well <] */
#include <stdio.h>


/** This produces a divide-by-zero FPE for i = 800. */
double do_stuff(int i){
  return 123.456 / (i - 800);
}


int main(void) {

  /* To pick and choose which type of FPE to raise: */
  /* feenableexcept(FE_DIVBYZERO); */
  /* Options are: (Combine through binary OR) */
  /* feenableexcept(FE_DIVBYZERO |
   *                FE_INEXACT |
   *                FE_INVALID |
   *                FE_OVERFLOW |
   *                FE_UNDERFLOW); */
  /* Alternatively, just enable all: */
  /* feenableexcept(FE_ALL_EXCEPT); */

  const int elements = 1000;

  for (int i = 0; i < elements; i++){

    double val = do_stuff(i);

    if (i % 100 == 0)
      printf("%4d/%d, val=%g\n", i, elements, val);

  }

  return 0;
}


