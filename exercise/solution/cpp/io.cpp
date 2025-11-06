#include "io.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


/**
 * @brief Write output of step at time t.
 *
 * @param snapshot: Current snapshot number
 * @param step:     Current step of the simulation
 * @param t:        Current time of the simulation
 * @param grid:     The grid
 * @param ncells:   Number of (non-ghost) cells
 * @param nghosts:  Number of ghost cells on each boundary
 */
void io_write_output(int &snapshot,
                     int step,
                     float t,
                     Grid& grid,
                     int ncells,
                     int nghosts) {

  if (snapshot > 9999){
    std::cerr << "I'm not made to write outputs > 9999" << std::endl;
    std::abort();
  }

  /* generate output filename for this snapshot */
  char filename[MAX_FNAME_SIZE] = "";
  char snapnrstr[12] = "";

  std::stringstream fname;
  fname << "output_";
  fname << std::setfill('0') << std::setw(4) << snapshot;
  fname << ".dat";

  std::string fname_str = fname.str();

  std::cout << "Step " << step << ": Dumping output to " << fname_str;
  std::cout << " for t= " << t << "\n";

  /* Write output file */
  /* First a header */
  std::ofstream out(fname_str);

  out << "# ncells = " << std::setw(12) <<  ncells << "\n";
  out << "# t = " << std::setw(12) << std::setprecision(6) << t << "\n";
  out << "# nsteps = " << std::setw(12) <<  step << "\n";
  out << "# x           q            \n";

  /* Now the actual cell content */
  for (int i = nghosts; i < ncells + nghosts; i++) {
    Cell& c = grid.get_cell(i);
    out << std::setw(12) << std::setprecision(6) << (c.index - nghosts + 0.5) * c.dx;
    out << ",";
    out << std::setw(12) << std::setprecision(6) << c.q_old;
    out << "\n";
  }

  out.close();

  /* raise snapshot number */
  snapshot += 1;
}
