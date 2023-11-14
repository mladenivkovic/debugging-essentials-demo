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

void cell_first_init(struct cell* cells, const int N, const double dx);
void cell_copy(struct cell* src, struct cell* dest);

#endif
