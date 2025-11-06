/* Functions containing the actual solver. */

#include "solver.h"

/**
 * Compute the maximal permissible time step size.
 * This mimics the behaviour of a general solver, where we would need to compute
 * the maximal perimissible time step size each step because it will depend on
 * the current state of the solution. For linear advection with constant
 * coefficients however, this should always be the same identical value.
 *
 * @param grid the #grid containing cells
 * @param N number of cells in array
 * @param CFL_factor the Courant-Friedrichs-Levy factor
 *
 * @return dt_max the maximally permissible time step size for this step.
 */
double solver_find_next_time_step_size(Grid &grid, int N, double CFL_factor){

  double dt_max = 0.;
  for (int i = 0; i < N; i++) {
    Cell &c = grid.get_cell(i);
    double dt = c.dx / c.a;
    if (dt > dt_max) dt_max = dt;
  }

  return CFL_factor * dt_max;
}



/**
 * Solve the linear advection equation on arrays of values.
 *
 * @param q_old (in) array of current values of the conserved quantity
 * @param q_new (out) array of results after the time integration
 * @param a array of advection coefficients
 * @param dx array of cell widths
 * @param N size of all arrays above
 * @param dt current time step size
 */
void solver_solve_on_array(const double q_old[VECTOR_SIZE],
                           double q_new[VECTOR_SIZE],
                           const double a[VECTOR_SIZE],
                           const double dx[VECTOR_SIZE],
                           int N,
                           double dt){

  for (int i = 1; i < N; i++){
    q_new[i] = q_old[i] + a[i] * dt / dx[i] * (q_old[i-1] - q_old[i]);
  }
}



/**
 * Main routine to solve a single step.
 *
 * As a minor optimization technique, we convert the array-of-structs `cells`
 * into a struct-of-arrays, or in this case just contiguous arrays of the
 * quantities required to compute the actual solution. We then compute the
 * solution using these arrays, first store it in a different array, and finally
 * copy the solution back to the `cells`.
 *
 * @param grid the grid containing the cells
 * @param N number of non-ghost cells in array
 * @param nghost number of boundary ghost cells
 * @param dt the time step size to integrate over.
 */
void solver_step(Grid &grid, int N, int nghost, double dt){

  /* Total number of cells */
  const int ncells_tot = 2 * (N + nghost);

  /* Loop over all cells, including ghost cells, in chunks of VECTOR_SIZE.
   * However, we always need to access and read the element i - 1 in our update
   * formula. So the first element in our arrays is read-only, and will never
   * be updated. Therefore, all the corresponding loops start at index 1. In turn
   * we jump over index intervals of size VECTOR_SIZE - 1 such that the last
   * actually updated value will be the zeroth element in the subsequent loop, and
   * thus read-only. */
  for (int i = 0; i < ncells_tot; i += VECTOR_SIZE - 1){

    /* old state q(x) */
    double* q_old = new double[VECTOR_SIZE];
    /* new state q(x), i.e. state containing solution */
    double* q_new = new double[VECTOR_SIZE];
    /* advection coefficients. */
    double* a = new double[VECTOR_SIZE];
    /* advection coefficients. */
    double* dx = new double[VECTOR_SIZE];

    /* Gather data into arrays */
    for (int j = 0; j < VECTOR_SIZE; j++){
      Cell& c = grid.get_cell(i + j);
      q_old[j] = c.q_old;
      q_new[j] = 0.;
      a[j] = c.a;
      dx[j] = c.dx;
    }

    /* Call the actual solver */
    solver_solve_on_array(q_old, q_new, a, dx, VECTOR_SIZE, dt);

    /* Copy solution back into array-of-structs */
    for (int j = 1; j < VECTOR_SIZE; j++){
      Cell& c = grid.get_cell(i + j);
      c.q_new = q_new[j];
    }
  }

  /* Once we're finished, copy the result back from q_new into q_old */
  for (int i = 0; i < ncells_tot; i++){
      Cell& c = grid.get_cell(i);
      c.q_old = c.q_new;
  }

}

