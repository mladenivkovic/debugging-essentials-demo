module initial_conditions

  use params
  use cell_module

  implicit none


contains

  !=========================================================
  ! Set up initial conditions.
  !
  ! @param ncells number of (non-ghost) cells in array
  ! @param nghosts number of ghost cells on boundaries
  ! @param cells array of cells
  ! @param boxsize size of simulated box
  ! @param a advection coefficient
  ! @param dx size of each cell
  !=========================================================
  subroutine ic_setup_initial_conditions(ncells, nghosts, cells, boxsize, a, dx)

    implicit none

    integer, intent(in)                                        :: ncells
    integer, intent(in)                                        :: nghosts
    type (cell), dimension(1:ncells+2*nghosts), intent(inout)  :: cells
    real(dp), intent(in)                                       :: boxsize
    real(dp), intent(in)                                       :: a
    real(dp), intent(in)                                       :: dx

    write(*,*) "Calling initial condition"

    call ic_setup_top_hat_inital_conditions(ncells, nghosts, cells, boxsize, a, dx)
  end subroutine ic_setup_initial_conditions


  !=========================================================
  ! Set up top hat initial conditions.
  ! q(x, t=t0) = 1 if x < 1/3 * boxsize or x > 2/3 * boxsize
  !            = 2 if 1/3 * boxsize <= x <= 2/3 * boxsize
  ! a(x, t) = a_0 = const
  !
  ! @param ncells number of (non-ghost) cells in array
  ! @param nghosts number of ghost cells on boundaries
  ! @param cells array of cells
  ! @param boxsize size of simulated box
  ! @param a advection coefficient
  ! @param dx size of each cell
  !=========================================================
  subroutine ic_setup_top_hat_inital_conditions(ncells, nghosts, cells, boxsize, a, dx)

    implicit none

    integer, intent(in)                                       :: ncells
    integer, intent(in)                                       :: nghosts
    type (cell), dimension(1:ncells+2*nghosts), intent(inout) :: cells
    real(dp), intent(in)                                      :: boxsize
    real(dp), intent(in)                                      :: a
    real(dp), intent(in)                                      :: dx

    integer :: i
    real(dp) :: x

    do i = 1, ncells + 2*nghosts
      cells(i)%a = a
      cells(i)%q_old = 1.d0
      x = (dble(i - nghosts) + 0.5d0) * dx
      if ( (boxsize / 3.d0 .le. x) .and. (x .le. 2.d0 * boxsize / 3.d0) ) then
        cells(i)%q_old = 2.d0
      endif
    enddo
  end subroutine ic_setup_top_hat_inital_conditions

end module initial_conditions
