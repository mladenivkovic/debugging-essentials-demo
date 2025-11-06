Introduced Bugs
=========================


- solver_step: Memory leak: Allocating arrays without freeing them
- solver_step: access out of bounds: VECTOR_SIZE is incorrect length of arrays when you reach the end of the loop 
- solver_step: access out of bounds: `ncells_tot = N + 2 * nghost` is correct formula
- bc_apply_periodic_boundary_conditions: access out of bounds when copying left boundary into right ghost cells.
- cell_first_init: dx not initialized. Leads to time step = 0 
- io_write_output: Should crash after 9999 snapshots, not after 9

