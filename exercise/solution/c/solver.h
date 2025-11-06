/* Functions containing the actual solver. */

#ifndef SOLVER_H
#define SOLVER_H

#include "cell.h"

/* Must be >= 2 */
#define VECTOR_SIZE 64

double solver_find_next_time_step_size(struct cell *cells, int N, double CFL_factor);
void solver_solve_on_array(double* q_old, double* q_new, double* a, double* dx, int N, double dt);
void solver_step(struct cell* cells, int N, int nghost, double dt);

#endif
