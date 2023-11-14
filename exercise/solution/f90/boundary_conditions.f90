module boundary_conditions

  use cell_module
  use params

  implicit none

  contains

  ! ===============================================================
  ! Apply periodic boundary conditions.
  !
  ! @param ncells: number of non-ghost cells in array
  ! @param nghosts: number of ghost cells on each boundary
  ! @param cells: array of all cells
  ! ===============================================================
  subroutine bc_apply_periodic_boundary_conditions(ncells, nghosts, cells)

    implicit none

    integer, intent(in)                                       :: ncells
    integer, intent(in)                                       :: nghosts
    type (cell), dimension(1:ncells+2*nghosts), intent(inout) :: cells

    integer :: i

    ! Copy content of right boundary into left ghost cells
    do i = 1, nghosts
      ! start at index of last actual cell - nghosts
      ! index of last actual cell = nghosts + ncells
      call cell_copy(cells(ncells+i), cells(i))
    enddo

    ! Copy content of left boundary into right ghost cells
    do i = 1, nghosts
      ! Start at index of first actuall cell, which is = nghosts
      call cell_copy(cells(nghosts+i), cells(ncells+nghosts+i))
    enddo
  end subroutine bc_apply_periodic_boundary_conditions


  ! ===============================================================
  ! Main function to apply boundary conditions.
  !
  ! @param ncells: number of non-ghost cells in array
  ! @param nghosts: number of ghost cells on each boundary
  ! @param cells: array of all cells
  ! ===============================================================
  subroutine bc_apply_boundary_conditions(ncells, nghosts, cells)

    implicit none

    integer, intent(in)                                       :: ncells
    integer, intent(in)                                       :: nghosts
    type (cell), dimension(0:ncells+2*nghosts), intent(inout) :: cells

    call bc_apply_periodic_boundary_conditions(ncells, nghosts, cells);

  end subroutine bc_apply_boundary_conditions

end module boundary_conditions
