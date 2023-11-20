#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

void error_exit(char *message){

  printf("Caught an error: %s\n", message);
  fflush(stdout);
  abort();
}

#endif
