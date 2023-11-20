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
 * create a breakpoint, and then add a watchpoint there. */
int sum;

int main(void) {

  sum = 0;

  for (int i = 0; i < 10; i++){
    do_stuff(&sum);
    sum += 1;
  }


  printf("Sum is %d\n", sum);
  printf("Done. Bye\n");

  return 0;
}
