module cell_module

  use params

  implicit none

  ! Definition of a cell
  type cell
    ! Index of this cell in the global array of cells
    integer  :: index
    ! Advected quantity, i.e. q(x, t), at the current time step
    real(dp) :: q_old
    ! Advected quantity, i.e. q(x, t+dt), at the end of the time step
    real(dp) :: q_new
    ! Advection coefficient at this location
    real(dp) :: a
    ! This cell's size
    real(dp) :: dx
  end type cell



  contains

    !=====================================================
    ! Initialize array of cells to default values.
    !
    ! @param cells Array of cells
    ! @param N number of cells in array
    !=====================================================
    subroutine cell_first_init(N, cells)

      implicit none
      integer, intent(in)                        :: N
      type (cell), dimension(1:N), intent(inout) :: cells

      integer :: i

      do  i = 1, N
        cells(i)%index = i
        cells(i)%q_old = 0.d0
        cells(i)%q_new = 0.d0
        cells(i)%a = 0.d0
      enddo
    end subroutine cell_first_init


    !=====================================================
    ! Copy the contents of a cell `src` to a cell `dest
    !=====================================================
    subroutine cell_copy(src, dest)

      implicit none
      type(cell), intent(in)  :: src
      type(cell), intent(out) :: dest

      dest%index = src%index
      dest%q_old = src%q_old
      dest%q_new = src%q_new
      dest%a = src%a
      dest%dx = src%dx

    end subroutine cell_copy

end module cell_module
