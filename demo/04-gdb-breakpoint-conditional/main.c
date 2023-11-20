#include <stdio.h>

int main(void) {

  int sum = 0;

  for (int i = 0; i < 10; i++){

    sum += i;
    printf("Running loop i == %i\n", i);

  }

  printf("Sum is %d\n", sum);
  printf("Done. Bye\n");

  return 0;
}
