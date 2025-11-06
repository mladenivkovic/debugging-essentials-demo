#pragma once

#include "cell.h"

class Grid {

  /**
   *@brief Class to store the cells in a grid.
   */

public:
  /*! Constructor: Allocates cells array */
  Grid(int n_cells);

  /*! Destructor: Frees cells array */
  ~Grid();

  /*! Apply boundary conditions */
  void apply_boundary_conditions(int ncells, int nghosts);

  /*! First default init of cells */
  void first_init_cells(double dx);

  /*! Get reference to a cell by index */
  Cell& get_cell(int index);

  /*! Impose initial conditions */
  void setup_initial_conditions(int N,
                                int nghosts,
                                double boxsize,
                                double a,
                                double dx);

private:

  /*! Array of cells */
  Cell* _cells;

  /*! Number of cells stored in grid */
  int _count;

};
