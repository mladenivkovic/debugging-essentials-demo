#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* sleep */


int main(int argc, char* argv[]){

  int rank, size;

  /* initialize MPI */
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /* print a greeting from each rank once every second 100 times */
  for (int i = 0; i < 100; i++) {
    printf("Hello from rank %d! i=%d\n", rank, i);
    sleep(1);

    /* Show off gdb catching errors while MPI is running. */
    if (i == 20 && rank == 2){
      abort(); /* this should raise an error. */
    }
  }

  /* no more MPI routines after this point */
  MPI_Finalize();
}
