/* To use feenableexcept() with gcc, you need to define the macro below first. */
/* #define _GNU_SOURCE */
/* With the intel icx compiler, you need to compile the program with the -fp-model=strict flag. */
#include <fenv.h>
#include <stdio.h>

/**
 * A function that first recurses down a couple of
 * levels so we have something to look at in the
 * backtrace. Then produces an FPE at some point. */
double some_recursive_function(int i, int depth){

  if (depth >= 6) {
    /* produce an FPE (divide by zero) at i == 800 */
    double val = 123.456 / (i - 800);
    return val;
  }
  else {
    return some_recursive_function(i, depth+1);
  }
}


int main(void) {

  /* To pick and choose which type of FPE to raise: */
  feenableexcept(FE_DIVBYZERO | FE_INEXACT | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW);
  /* Alternatively, just enable all: */
  /* feenableexcept(FE_ALL_EXCEPT); */

  const int elements = 1000;

  for (int i = 0; i < elements; i++){

    double val = some_recursive_function(i, 0);

    if (i % 100 == 0)
      printf("%4d/%d, val=%g\n", i, elements, val);

  }


  return 0;
}
