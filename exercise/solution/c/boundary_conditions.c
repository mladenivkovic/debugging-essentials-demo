#include "boundary_conditions.h"

/**
 * Apply periodic boundary conditions.
 *
 * @param cells: array of all cells
 * @param ncells: number of non-ghost cells in array
 * @param nghosts: number of ghost cells on each boundary
 */
void bc_apply_periodic_boundary_conditions(struct cell* cells,
                                           int ncells,
                                           int nghosts){

  /* Copy content of right boundary into left ghost cells */
  for (int i = 0; i < nghosts; i++){
   /* start at index of last actual cell - nghosts
    * index of last actual cell = nghosts + ncells - 1 */
    struct cell* src = &cells[ncells - 1 + i];
    struct cell* dest = &cells[i];
    cell_copy(src, dest);
  }

  /* Copy content of left boundary into right ghost cells */
  for (int i = 0; i < nghosts; i++){
    /* Start at index of first actuall cell, which is = nghosts */
    struct cell* src = &cells[nghosts + i];
    struct cell* dest = &cells[ncells + nghosts + i];
    cell_copy(src, dest);
  }
}


/**
 * Main function to apply boundary conditions.
 *
 * @param cells: array of all cells
 * @param ncells: number of non-ghost cells in array
 * @param nghosts: number of ghost cells on each boundary
 */
void bc_apply_boundary_conditions(struct cell* cells,
                                  int ncells,
                                  int nghosts){

  bc_apply_periodic_boundary_conditions(cells, ncells, nghosts);
}
