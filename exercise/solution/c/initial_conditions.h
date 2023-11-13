/* Functions related to setting up initial conditions. */

#ifndef INITIAL_CONDITIONS_H
#define INITIAL_CONDITIONS_H

#include "cell.h"

/**
 * Set up top hat initial conditions.
 * q(x, t=t0) = 1 if x < 1/3 * boxsize or x > 2/3 * boxsize
 *            = 2 if 1/3 * boxsize <= x <= 2/3 * boxsize
 * a(x, t) = a_0 = const
 *
 * @param cells array of cells
 * @param N number of (non-ghost) cells in array
 * @param nghosts number of ghost cells on boundaries
 * @param boxsize size of simulated box
 * @param a advection coefficient
 * @param dx size of each cell
 */
void ic_setup_top_hat_inital_conditions(struct cell* cells,
                              const int N,
                              const int nghosts,
                              const double boxsize,
                              double a,
                              double dx) {

  for (int i = nghosts; i < N + nghosts; i++){
    struct cell *c = &(cells[i]);
    c->a = a;
    c->q_old = 1.;
    double x = (i + 0.5) * dx;
    if ((boxsize / 3. <= x) && (x <= 2. * boxsize / 3.)) {
      c->q_old = 2.;
    }
  }
}




/**
 * Set up initial conditions.
 *
 * @param cells array of cells
 * @param N number of (non-ghost) cells in array
 * @param nghosts number of ghost cells on boundaries
 * @param boxsize size of simulated box
 * @param a advection coefficient
 * @param dx size of each cell
 */
void ic_setup_initial_conditions(struct cell* cells,
                              const int N,
                              const int nghosts,
                              const double boxsize,
                              double a,
                              double dx) {
  ic_setup_top_hat_inital_conditions(cells, N, nghosts, boxsize, a, dx);
}

#endif
