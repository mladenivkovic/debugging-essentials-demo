#include <stdio.h>

#include "error.h"

void do_stuff(int a, int b){
  for (int i = a; i < b; i ++) {
    if (i == 7) {
      error_exit("Caught i=7");
    }
  }
}


void do_other_stuff(int a, int b){
  for (int i = a; i < b; i ++) {
    if (i == 7) {
      error_exit("Caught i=7");
    }
  }
}

int main(void) {

  do_stuff(-7, 6);
  do_other_stuff(1, 12);
  printf("Done. Bye\n");

  return 0;
}

