/* Functions related to setting up initial conditions. */

#pragma once

#include "cell.h"

void ic_setup_top_hat_inital_conditions(Cell& cell,
                                        int N,
                                        int nghosts,
                                        double boxsize,
                                        double a,
                                        double dx);

