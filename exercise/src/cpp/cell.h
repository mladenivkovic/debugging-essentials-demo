#pragma once

class Cell {

public:

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

  /*! Initialise this cell for the first time with empty values, except the index
   * of this cell in the grid and the cell size dx */
  void first_init(int index_, double dx_);

  /*! Copy the contents of this cell into another */
  void copy(Cell& dest);
};


