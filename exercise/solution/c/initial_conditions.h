/* Functions related to setting up initial conditions. */

#ifndef INITIAL_CONDITIONS_H
#define INITIAL_CONDITIONS_H

#include "cell.h"


void ic_setup_initial_conditions(struct cell* cells,
                              const int N,
                              const int nghosts,
                              const double boxsize,
                              double a,
                              double dx);
void ic_setup_top_hat_inital_conditions(struct cell* cells,
                                        const int N,
                                        const int nghosts,
                                        const double boxsize,
                                        double a,
                                        double dx);

#endif
