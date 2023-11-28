#include <stdio.h>


void do_stuff(int *sum){
  if (*sum > 10) {
    return;
  } else {
    *sum += 10;
  }
}

/* Watched variable needs to be in global scope if you want to
 * set a watchpoint at startup. If it isn't in the global scope,
 * e.g. if it's inside `int main(void){}`, you'll need to first
 * create a breakpoint, and then add a watchpoint there.
 * You can do that with `sum2`.
 * */
int sum;

int main(void) {

  sum = 0;
  int sum2 = 0;

  for (int i = 0; i < 10; i++){
    do_stuff(&sum);
    do_stuff(&sum2);
    sum += 1;
    sum2 += 1;
  }


  printf("sum is %d, sum2 is %d\n", sum, sum2);
  printf("Done. Bye\n");

  return 0;
}
