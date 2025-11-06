Introduced Bugs
=========================

- solver_step: Memory leak: Allocating arrays without freeing them
- solver_step: access out of bounds: `ncells_tot = ncells + 2 * nghosts` is the correct version
- solver_step: access out of bounds: VECTOR_SIZE is incorrect length of arrays when you reach the end of the loop 
- bc_apply_periodic_boundary_conditions: access out of bounds when copying left boundary into right ghost cells.
- cell_first_init: dx not initialized. Leads to time step = 0 
- io.f90:int_to_char: check should be 9999, not 9

