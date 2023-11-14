module params

  implicit none

  integer, parameter :: sp = selected_real_kind(6, 37)
  integer, parameter :: dp = selected_real_kind(15, 307)
  integer, parameter :: qp = selected_real_kind(30, 291)

  integer, parameter :: MAX_FNAME_SIZE = 80
  integer, parameter :: VECTOR_SIZE = 64 ! must be >= 2

end module params
