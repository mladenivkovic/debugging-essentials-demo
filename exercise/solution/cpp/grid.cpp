#include "grid.h"
#include "initial_conditions.h"

/**
 * @brief constructs the "grid"
 */
Grid::Grid(int n_cells) {

  _cells = new Cell[n_cells];
  _count = n_cells;

}


/**
 * @brief constructs the "grid"
 */
Grid::~Grid() {

  delete[] _cells;
}


/**
 * @brief apply (periodic) boundary conditions
 *
 * @param ncells: number of non-ghost cells in array
 * @param nghosts: number of ghost cells on each boundary
 */
void Grid::apply_boundary_conditions(int ncells, int nghosts){

  /* Copy content of right boundary into left ghost cells */
  for (int i = 0; i < nghosts; i++){
   /* start at index of last actual cell - nghosts
    * index of last actual cell = nghosts + ncells - 1 */
    Cell& src = _cells[ncells - 1 + i];
    Cell& dest = _cells[i];
    src.copy(dest);
  }

  /* Copy content of left boundary into right ghost cells */
  for (int i = 0; i < nghosts; i++){
    /* Start at index of first actuall cell, which is = nghosts */
    Cell& src = _cells[nghosts + i];
    Cell& dest = _cells[ncells + nghosts + i];
    src.copy(dest);
  }
}


/**
 * @brief run a first default initialisation of cells
 *
 * @param dx the cell size
 */
void Grid::first_init_cells(double dx){

  for (int i = 0; i < _count; i++){
    _cells[i].first_init(i, dx);
  }
}


/**
 * @brief Get reference to a cell by index
 */
Cell& Grid::get_cell(int index){
  return _cells[index];
}


/**
 * @brief Impose initial conditions
 *
 * @param N number of (non-ghost) cells in array
 * @param nghosts number of ghost cells on boundaries
 * @param boxsize size of simulated box
 * @param a advection coefficient
 * @param dx the cell size
 */
void Grid::setup_initial_conditions(int N,
                                    int nghosts,
                                    double boxsize,
                                    double a,
                                    double dx){

  for (int i = 0; i < _count; i++) {
    ic_setup_top_hat_inital_conditions(_cells[i], N, nghosts, boxsize, a, dx);
  }
}

