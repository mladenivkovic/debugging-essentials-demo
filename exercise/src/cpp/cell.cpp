/* Definition of the cell struct and related functions */

#include "cell.h"

/**
 * @brief Initialize array of cells to default values.
 *
 * @param index index of this cells in grid's array
 * @param dx size of this cell
 */
void Cell::first_init(int index_, double dx_){
  index = index_;
  q_old = 0.;
  q_new = 0.;
  a = 0.;
  dx = dx_;
}


/**
  * @brief Copy the contents of this cell into another
  *
  * @param dest cell to copy data into
 */
void Cell::copy(Cell& dest){

  dest.index = index;
  dest.q_old = q_old;
  dest.q_new = q_new;
  dest.a = a;
  dest.dx = dx;
}
