module solver

  use params
  use cell_module

  implicit none


  contains

    ! ================================================================================
    ! Compute the maximal permissible time step size.
    ! This mimics the behaviour of a general solver, where we would need to compute
    ! the maximal perimissible time step size each step because it will depend on
    ! the current state of the solution. For linear advection with constant
    ! coefficients however, this should always be the same identical value.
    !
    ! @param N number of cells in array
    ! @param cells array of all cells
    ! @param CFL_factor the Courant-Friedrichs-Levy factor
    !
    ! @return dt_max the maximally permissible time step size for this step.
    ! ================================================================================
    real(dp) function solver_find_next_time_step_size(N, cells, CFL_factor)

      implicit none
      integer, intent(in)                     :: N
      type (cell), dimension(1:N), intent(in) :: cells
      real(dp), intent(in)                    :: CFL_factor

      integer  :: i
      real(dp) :: dt_max, dt

      dt_max = 0.d0
      do i = 1, N
        dt = cells(i)%dx / cells(i)%a
        if (dt .gt. dt_max) then
          dt_max = dt
        endif
      enddo

      solver_find_next_time_step_size = CFL_factor * dt_max

    end function solver_find_next_time_step_size



    ! =========================================================================
    ! Solve the linear advection equation on arrays of values.
    ! This completes the full step in a naive way.
    !
    ! @param ncells number of (non-ghost) cells in array
    ! @param nghosts number of ghost cells on each boundary
    ! @param cells array of cells
    ! @param dt current time step size
    ! =========================================================================
    subroutine solver_step_unvectorized(ncells, nghosts, cells, dt)

      implicit none

      integer, intent(in)                                       :: ncells
      integer, intent(in)                                       :: nghosts
      type (cell), dimension(1:ncells+2*nghosts), intent(inout) :: cells
      real(dp), intent(in)                                      :: dt

      integer :: i
      real(dp) :: qi, qim1, a, dx

      do i = 2, ncells + 2 * nghosts
        qi = cells(i)%q_old
        qim1 = cells(i-1)%q_old
        a = cells(i)%a
        dx = cells(i)%dx
        cells(i)%q_new = qi + a * dt / dx * (qim1 - qi)
      enddo

      do i = 2, ncells + 2*nghosts
        cells(i)%q_old = cells(i)%q_new
      enddo
    end subroutine solver_step_unvectorized



    ! =========================================================================
    ! Solve the linear advection equation on arrays of values.
    ! This completes the full step in a naive way.
    !
    ! @param N size of all arrays above
    ! @param q_old (in) array of current values of the conserved quantity
    ! @param q_new (out) array of results after the time integration
    ! @param a array of advection coefficients
    ! @param dx array of cell widths
    ! @param dt current time step size
    ! =========================================================================
    subroutine solver_solve_on_array(N, q_old, q_new, a, dx, dt)

      implicit none

      integer, intent(in)                   :: N
      real(dp), dimension(1:N), intent(in)  :: q_old
      real(dp), dimension(1:N), intent(out) :: q_new
      real(dp), dimension(1:N), intent(in)  :: a
      real(dp), dimension(1:N), intent(in)  :: dx
      real(dp), intent(in)                  :: dt

      integer :: i

      do i = 2, N
        q_new(i) = q_old(i) + a(i) * dt / dx(i) * (q_old(i-1) - q_old(i))
      enddo

    end subroutine solver_solve_on_array



    ! =========================================================================================
    ! Main routine to solve a single step.
    !
    ! As a minor optimization technique, we convert the array-of-structs `cells`
    ! into a struct-of-arrays, or in this case just contiguous arrays of the
    ! quantities required to compute the actual solution. We then compute the
    ! solution using these arrays, first store it in a different array, and finally
    ! copy the solution back to the `cells` structs.
    !
    ! @param ncells number of non-ghost cells in array
    ! @param nghost number of boundary ghost cells
    ! @param cells array of all cells
    ! @param dt the time step size to integrate over.
    ! =========================================================================================
    subroutine solver_step(ncells, nghosts, cells, dt)

      implicit none

      integer, intent(in)                                       :: ncells
      integer, intent(in)                                       :: nghosts
      type (cell), dimension(1:ncells+2*nghosts), intent(inout) :: cells
      real(dp), intent(in)                                      :: dt


      integer :: ncells_tot, nelements
      integer :: i, j

      ! old state q(x)
      real(dp), dimension(:), allocatable :: q_old
      ! new state q(x), i.e. state containing solution
      real(dp), dimension(:), allocatable :: q_new
      ! advection coefficients.
      real(dp), dimension(:), allocatable :: a
      ! cell widths
      real(dp), dimension(:), allocatable :: dx

      allocate(q_old(1:VECTOR_SIZE))
      allocate(q_new(1:VECTOR_SIZE))
      allocate(a(1:VECTOR_SIZE))
      allocate(dx(1:VECTOR_SIZE))

      ! Total number of cells
      ncells_tot = ncells + 2 * nghosts

      ! Loop over all cells, including ghost cells, in chunks of VECTOR_SIZE.
      ! However, we always need to access and read the element i - 1 in our update
      ! formula. So the first element in our arrays is read-only, and will never
      ! be updated. Therefore, all the corresponding loops start at index 1. In turn
      ! we jump over index intervals of size VECTOR_SIZE - 1 such that the last
      ! actually updated value will be the zeroth element in the subsequent loop, and
      ! thus read-only.

      do i = 1, ncells_tot, VECTOR_SIZE - 1
    !   for (int i = 1; i < ncells_tot; i += VECTOR_SIZE - 1){
    !
        ! How many elements are we actually working on?
        nelements = VECTOR_SIZE;
        if (i + VECTOR_SIZE > ncells_tot) then
          nelements = ncells_tot - i
        endif

        ! Gather data into arrays
        do j = 1, nelements
    !     for (int j = 0; j < nelements; j++){
          q_old(j) = cells(i+j)%q_old;
          q_new(j) = 0.;
          a(j) = cells(i+j)%a;
          dx(j) = cells(i+j)%dx;
        enddo


        ! Call the actual solver
        call solver_solve_on_array(nelements, q_old, q_new, a, dx, dt);


        ! Copy solution back into array-of-structs
        do j = 2, nelements
          cells(i+j)%q_new = q_new(j);
        enddo
      enddo


      ! Once we're finished, copy the result back from q_new into q_old
      do i = 1, ncells_tot
        cells(i)%q_old = cells(i)%q_new;
      enddo

      ! Clean up after yourself
      deallocate(q_old);
      deallocate(q_new);
      deallocate(a);
      deallocate(dx);

    end subroutine solver_step

end module solver
