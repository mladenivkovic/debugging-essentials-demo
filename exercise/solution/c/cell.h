/* Definition of the cell struct and related functions */

#ifndef CELL_H
#define CELL_H


struct cell {
  /*! Index of this cell in the global array of cells */
  int index;
  /*! Advected quantity, i.e. q(x, t), at the current time step */
  double q_old;
  /*! Advected quantity, i.e. q(x, t+dt), at the end of the time step */
  double q_new;
  /*! Advection coefficient at this location */
  double a;
  /*! This cell's size */
  double dx;
};


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
    cells[i].dx = dx;
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

#endif
