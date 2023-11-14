/**
 * Main file for the linear advection solver.
 * This is the solution file, which should be bug-free.
 */

#include "boundary_conditions.h"
#include "cell.h"
#include "initial_conditions.h"
#include "io.h"
#include "solver.h"

#include <stdlib.h>
#include <stdio.h>


/* First we define some global simulation parameters here. */


/* Time step related variables */
/* --------------------------- */

/*! End of simulation time */
const double t_end = 1.0;
/*! Time interval between output writings */
const double delta_t_output = 0.1;
/*! Maximal number of steps to take.
 * Mainly intended as an emergency halt if something goes wrong.*/
const int max_nr_steps = 1000000;
/*! How many steps between writing log to screen */
const int delta_step_log = 100;


/* Advection related variables */
/* --------------------------- */

/*! Advection coefficient */
const double a = 2.;
/*! Courant-Friedrichs-Levy factor */
const double CFL_factor = 0.9;


/* Grid and cell related variables */
/* ------------------------------- */

/*! Number of cells we use */
const int ncells = 10000;
/*! number of ghost cells used to enforce periodic boundary conditions */
const int nghosts = 2;
/*! Size of the box being simulated */
const double boxsize = 2.;
/*! size of a cell */
const double dx = boxsize / (double) (ncells + 1);




int main(void){

  /* Total number of cells that we have in our global array */
  int ncells_tot = ncells + 2 * nghosts;

  /* First allocate a grid of cells */
  struct cell *cells = malloc(ncells_tot * sizeof(struct cell));
  /* Initialize default values */
  cell_first_init(cells, ncells_tot, dx);
  /* Impose initial conditions */
  ic_setup_initial_conditions(cells, ncells, nghosts, boxsize, a, dx);


  /* Prepare to run */
  double t = 0.;
  double dt = 0.;
  int step = 0;
  double next_output_time = 0.;
  int write_output = 0;
  int snapshot = 0;

  /* Write initial output of initial conditions. */
  io_write_output(&snapshot, step, t, cells, ncells, nghosts);
  next_output_time += delta_t_output;


  /* Main simulation loop */
  /* max_nr_steps is mainly used as an emergency break to prevent
   * infinite loops. */
  while ( t < t_end && step < max_nr_steps){

    /* Apply periodic boundary conditions */
    bc_apply_boundary_conditions(cells, ncells, nghosts);

    /* First find the next time step size. */
    dt = solver_find_next_time_step_size(cells, ncells_tot, CFL_factor);

    /* If we need to write output, we might need to restrict dt to finish
     * integrating to the exact time we want. */
    if (t + dt > next_output_time){
      dt = next_output_time - t;
      next_output_time += delta_t_output;
      write_output = 1; /* flag that we're writing output now. */
    }

    /* Run the actual solver step */
    solver_step(cells, ncells, nghosts, dt);

    /* Are we writing output? */
    if (write_output) {
      io_write_output(&snapshot, step, t, cells, ncells, nghosts);
      write_output = 0;
    }

    /* Are we writing some log to the screen? */
    if (step % delta_step_log == 0){
      printf("Step %6d  t=%12.6e  dt=%12.6e\n", step, t, dt);
    }

    /* Increase time and step counter */
    t += dt;
    step++;
  }

  /* If we ran out of max steps, warn the user about it. */
  if (step == max_nr_steps){
    printf("WARNING: Reached max nr of steps to run, not specified simulation end time.\n");
  }

  /* If we didn't write any output at the last step, do it now. */
  if (write_output) {
    io_write_output(&snapshot, step, t, cells, ncells, nghosts);
    write_output = 0;
  }

  /* Have we skipped writing a log to screen in the last step? */
  if ((step-1) % delta_step_log != 0){
    printf("Step %6d  t=%12.6e  dt=%12.6e\n", step-1, t-dt, dt);
  }

  /* Say good-bye */
  printf("Done, bye.\n");

  /* Clean up after yourself */
  free(cells);

  return 0;
}
