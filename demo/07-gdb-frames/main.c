#include <stdio.h>

/* A set of functions calling each other so we can create a
 * deep stack trace. */
int level_5(int a){
  a += 5;
  return a;
}
int level_4(int a){
  a += 4;
  return level_5(a);
}
int level_3(int a){
  a += 3;
  return level_4(a);
}
int level_2(int a){
  a += 2;
  return level_3(a);
}
int level_1(int a){
  a += 1;
  return level_2(a);
}
int level_0(int a){
  a += 0;
  return level_1(a);
}


int main(void) {

  int a = 1;
  int res = level_0(a);

  printf("Result = %d\n", res);
  printf("Done. Bye\n");

  return 0;
}
