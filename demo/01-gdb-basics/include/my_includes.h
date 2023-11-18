#include "my_struct.h"
#include <math.h>


/**
 * Just do some stuff.
 **/
void do_stuff(double* val, int i, struct my_struct* s){

  double temp = exp(23. * sin(i * 3.1415926 / 137.));

  if (i % 100000 == 3)
    temp = -exp(23. * sin(i * 3.1415926 / 137.)) + s->whatever;

  *val = temp;


}
