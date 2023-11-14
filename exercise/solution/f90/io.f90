module io

  use params
  use cell_module

  contains

    ! ==============================================
    ! Convert an integer with up to 4 digits into
    ! a zero padded character string
    !
    ! @param n integer to convert
    ! @param nchar integer as zero-padded character
    ! ==============================================
    subroutine int_to_char(n, nchar)
      implicit none
      integer, intent(in)           :: n
      character(len=4), intent(out) :: nchar

      character(len=1)::nchar1
      character(len=2)::nchar2
      character(len=3)::nchar3
      character(len=4)::nchar4

      if (n .gt. 9999) then
        write(7, *) "I'm not made to write outputs > 9999"
        stop
      endif

      if(n.ge.1000)then
         write(nchar4,'(i4)') n
         nchar = nchar4
      elseif(n.ge.100)then
         write(nchar3,'(i3)') n
         nchar = '0'//nchar3
      elseif(n.ge.10)then
         write(nchar2,'(i2)') n
         nchar = '00'//nchar2
      else
         write(nchar1,'(i1)') n
         nchar = '000'//nchar1
      endif
    end subroutine int_to_char


    !=============================================================
    ! Write output of step at time t.
    !
    ! @param snapshot: (Pointer to) current snapshot number
    ! @param step:     Current step of the simulation
    ! @param t:        Current time of the simulation
    ! @param ncells:   Number of (non-ghost) cells
    ! @param nghosts:  Number of ghost cells on each boundary
    ! @param cells:    Array of all cells
    !=============================================================
    subroutine io_write_output(snapshot, step, t, ncells, nghosts, cells)

      implicit none

      integer, intent(inout)                                  :: snapshot
      integer, intent(in)                                     :: step
      real(dp), intent(in)                                    :: t
      integer, intent(in)                                     :: ncells
      integer, intent(in)                                     :: nghosts
      type (cell), dimension(1:ncells+2*nghosts), intent(in)  :: cells

      integer                       :: i
      type (cell)                   :: c
      character(len=MAX_FNAME_SIZE) :: filename
      character(len=4)              :: snapstr

      ! generate output filename for this snapshot
      call int_to_char(snapshot, snapstr)
      filename = TRIM("output_") // TRIM(snapstr) // ".dat"

      write(*, '(A4,1x,i6,1x,A20,A16,1x,A6,1x,ES12.3E2)') &
        "Step", step, ": Dumping output to ", filename, "for t=", t

      ! Write output file
      ! First a header
      open(unit = 1, file=filename)
      write(1, '(A,i12)') "# ncells = ", ncells
      write(1, '(A,ES12.3E2)') "# t = ", t
      write(1, '(A,i12)') "# nsteps = ", step

      ! Now the actual cell content
      write(1, '(A1,A12,A13)') "#", "x", "q"

      do i = nghosts, ncells + nghosts - 1
        c = cells(i)
        write(1, '(ES14.6E3,A1,ES14.6E3)') &
          (dble(c%index - nghosts) + 0.5d0) * c%dx, ",", c%q_old
      enddo

      close(1)

      ! raise snapshot number
      snapshot = snapshot + 1

    end subroutine io_write_output


end module io
