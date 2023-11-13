Introduced Bugs
=========================


- Memory leak in solver_step: Allocating arrays without freeing them
- solver_step: access out of bounds: VECTOR_SIZE is incorrect length of arrays when you reach the end of the loop 
- bc_apply_periodic_boundary_conditions: access out of bounds when copying left boundary into right ghost cells.
- bc_apply_periodic_boundary_conditions: copying right boundary into left cells is being copied into wrong celcopying right boundary into left cells is being copied into wrong cell
- cell_first_init: dx not initialized. Leads to time step = 0 

