#include <stdlib.h>


int main(void){

  int n = 10;

  /* allocate array of arrays */
  int** arr = malloc(n * sizeof(int*));
  for (int i = 0; i < n; i++) {
    arr[i] = malloc(n * sizeof(int));
  }

  /* now do some useless thing with them */
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      arr[i][j] = i*n + j;
    }
  }

  /* We "forget" to free some arrays now */
  free(arr);

}
