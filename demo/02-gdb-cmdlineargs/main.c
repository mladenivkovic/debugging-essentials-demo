#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc <= 1){
    printf("Error: You need to provide at least 1 cmdline argument.\n");
    abort();
  }

  for (int i = 1; i < argc; i++) {
    printf("Cmdline argument %d was '%s'\n", i, argv[i]);
  }

  printf("Done. Bye\n");

  return 0;
}

