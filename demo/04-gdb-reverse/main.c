#include <stdio.h>

int main(void) {

  int sum = 0;

  for (int i = 0; i < 10; i++){

    sum += i;

    if (i == 5) {
      printf("Caught i == 5\n");
    }
  }

  printf("Sum is %d\n", sum);
  printf("Done. Bye\n");

  return 0;
}
