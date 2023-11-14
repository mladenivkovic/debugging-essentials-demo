#include "cell.h"

/**
 * Initialize array of cells to default values.
 *
 * @param cells Array of cells
 * @param N number of cells in array
 * @param dx size of this cell
 */
void cell_first_init(struct cell* cells, const int N, const double dx){
  for (int i = 0; i < N; i++){
    cells[i].index = i;
    cells[i].q_old = 0.;
    cells[i].q_new = 0.;
    cells[i].a = 0.;
  }
}


/**
 * Copy the contents of a cell `src` to a cell `dest`
 */
void cell_copy(struct cell* src, struct cell* dest){

    dest->index = src->index;
    dest->q_old = src->q_old;
    dest->q_new = src->q_new;
    dest->a = src->a;
    dest->dx = src->dx;
}

