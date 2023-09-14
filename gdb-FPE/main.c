#define _GNU_SOURCE /* for FPEs */
#include <fenv.h>   /* for FPEs */
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

  /* enables floating point exceptions */
  feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);
  /* feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW); */

  const int elements = 1000;

  for (int i = 0; i < elements; i++){

    /* double val = 123.456 / (i - 800); */
    double val = some_recursive_function(i, 0);

    /* printf("%4d/%d, val=%g\n", i, elements, val); */
    if (i % 1000 == 0)
      printf("%4d/%d, val=%g\n", i, elements, val);

  }


  return 0;
}
