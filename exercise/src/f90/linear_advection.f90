program linear_advection

  use boundary_conditions
  use cell_module
  use initial_conditions
  use io
  use params
  use solver

  implicit none

  ! Time step related variables
  ! ---------------------------
  ! End of simulation time
  real(dp), parameter:: t_end = 1.0d0
  ! Time interval between output writings
  real(dp), parameter:: delta_t_output = 0.1d0
  ! Maximal number of steps to take.
  ! Mainly intended as an emergency halt if something goes wrong.
  integer, parameter::  max_nr_steps = 1000000
  ! How many steps between writing log to screen
  integer, parameter::  delta_step_log = 100


  ! Advection related variables
  ! ---------------------------
  ! Advection coefficient
  real(dp), parameter:: a = 2.d0
  ! Courant-Friedrichs-Levy factor
  real(dp), parameter:: CFL_factor = 0.9d0


  ! Grid and cell related variables
  ! -------------------------------
  ! Number of cells we use
  integer, parameter  :: ncells = 10000
  ! number of ghost cells used to enforce periodic boundary conditions
  integer, parameter  :: nghosts = 2
  ! Size of the box being simulated
  real(dp), parameter :: boxsize = 2.d0
  ! size of a cell
  real(dp), parameter :: dx = boxsize / dble(ncells + 1)



  ! Now for some local variables.
  ! ------------------------------
  ! Total number of cells we have
  integer  :: ncells_tot
  ! Current step number
  integer  :: step
  ! Current snapshot (output) number
  integer  :: snapshot
  ! Are we writing output this step?
  logical  :: write_output
  ! Current simulation time
  real(dp) :: t
  ! Current time step size
  real(dp) :: dt
  ! time at which next snapshot is written
  real(dp) :: next_output_time

  ! Array of all cells
  type (cell), dimension(:), allocatable :: cells



  ! Total number of cells that we have in our global array
  ncells_tot = ncells + 2 * nghosts

  ! First allocate a grid of cells
  allocate(cells(1:ncells_tot))
  ! Initialize default values
  call cell_first_init(ncells_tot, cells)
  ! Impose initial conditions
  call ic_setup_initial_conditions(ncells, nghosts, cells, boxsize, a, dx)


  ! Prepare to run
  t = 0.d0
  dt = 0.d0
  step = 0
  next_output_time = 0.d0
  write_output = .false.
  snapshot = 0


  ! Write initial output of initial conditions.
  call io_write_output(snapshot, step, t, ncells, nghosts, cells)
  next_output_time = next_output_time + delta_t_output


  ! Main simulation loop
  ! max_nr_steps is mainly used as an emergency break to prevent infinite loops.
  do while ( t < t_end .and. step < max_nr_steps)

    ! Apply periodic boundary conditions
    call bc_apply_boundary_conditions(ncells, nghosts, cells);

    ! First find the next time step size.
    dt = solver_find_next_time_step_size(ncells_tot, cells, CFL_factor);

    ! If we need to write output, we might need to restrict dt to finish
    ! integrating to the exact time we want.
    if (t + dt .gt. next_output_time) then
      dt = next_output_time - t
      next_output_time = next_output_time + delta_t_output
      write_output = .true.
    endif

    ! Run the actual solver step
    call solver_step(ncells, nghosts, cells, dt)

    ! Are we writing output?
    if (write_output) then
        call io_write_output(snapshot, step, t, ncells, nghosts, cells)
        write_output = .false.
    endif

    ! Are we writing some log to the screen? */
    if (mod(step,delta_step_log) .eq. 0) then
      write(*, '(A5,i6,A4,1x,ES13.6E2,1x,A4,ES12.6E2)') &
        "Step ", step, "t=", t, "dt=", dt
    endif

    ! Increase time and step counter
    t = t + dt;
    step = step + 1

  enddo


  ! If we ran out of max steps, warn the user about it.
  if (step .eq. max_nr_steps) then
    write(*, *) &
      "WARNING: Reached max nr of steps to run, not specified simulation end time."
  endif

  ! If we didn't write any output at the last step, do it now.
  if (write_output) then
    call io_write_output(snapshot, step, t, ncells, nghosts, cells)
    write_output = .false.
  endif

  ! Have we skipped writing a log to screen in the last step?
  if (mod((step-1),delta_step_log) .ne. 0) then
    write(*, '(A5,i6,A4,1x,ES12.6E2,1x,A4,ES12.6E2)') &
      "Step ", step, "t=", t, "dt=", dt
  endif

  ! Say good-bye
  write(*, *) "Done, bye."

  ! clean up after yourself
  deallocate(cells)

end program linear_advection
