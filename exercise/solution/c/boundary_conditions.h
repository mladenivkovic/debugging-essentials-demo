#ifndef BOUNDARY_CONDITIONS_H
#define BOUNDARY_CONDITIONS_H

#include "cell.h"

void bc_apply_boundary_conditions(struct cell* cells, const int ncells, const int nghosts);
void bc_apply_periodic_boundary_conditions(struct cell* cells, const int ncells, const int nghosts);

#endif
