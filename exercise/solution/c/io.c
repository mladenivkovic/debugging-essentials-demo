#include "io.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** Write output of step at time t.
 *
 * @param snapshot: (Pointer to) current snapshot number
 * @param step:     Current step of the simulation
 * @param t:        Current time of the simulation
 * @param cells:    Array of all cells
 * @param ncells:   Number of (non-ghost) cells
 * @param nghosts:  Number of ghost cells on each boundary
 */
void io_write_output(int *snapshot,
                     int step,
                     float t,
                     struct cell* cells,
                     int ncells,
                     int nghosts) {

  if (*snapshot > 9999){
    fprintf(stderr, "I'm not made to write outputs > 9999\n");
    fflush(stderr);
    abort();
  }

  /* generate output filename for this snapshot */
  char filename[MAX_FNAME_SIZE] = "";
  char snapnrstr[12] = "";

  strcpy(filename, "output_");
  sprintf(snapnrstr, "%04d", *snapshot);
  strcat(filename, snapnrstr);
  strcat(filename, ".dat");

  printf("Step %d : Dumping output to %s for t= %g\n", step, filename, t);

  /* Write output file */
  /* First a header */
  FILE *outfilep = fopen(filename, "w");
  fprintf(outfilep, "# ncells = %10d\n", ncells);
  fprintf(outfilep, "# t = %12.6lf\n", t);
  fprintf(outfilep, "# nsteps = %12d\n", step);

  /* Now the actual cell content */
  fprintf(outfilep, "#%11s,%12s\n", "x", "q");
  for (int i = nghosts; i < ncells + nghosts; i++) {
    struct cell c = cells[i];
    fprintf(outfilep, "%12.6e,%12.6e\n", (c.index - nghosts + 0.5) * c.dx, c.q_old);
  }

  fclose(outfilep);

  /* raise snapshot number */
  *snapshot += 1;
}
