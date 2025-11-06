/* Functions containing the actual solver. */
#pragma once

#include "grid.h"

/* Must be >= 2 */
constexpr int VECTOR_SIZE = 64;

double solver_find_next_time_step_size(Grid &grid, int N, double CFL_factor);
void solver_solve_on_array(const double q_old[VECTOR_SIZE],
                           double q_new[VECTOR_SIZE],
                           const double a[VECTOR_SIZE],
                           const double dx[VECTOR_SIZE],
                           int N,
                           double dt);
void solver_step(Grid &grid, int N, int nghost, double dt);

