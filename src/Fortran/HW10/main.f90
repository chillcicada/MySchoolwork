program main
  use mpi
  implicit none

  integer, parameter :: length = 64
  integer, parameter :: itcs = 100
  integer :: x, y, i, j, itc
  integer :: ierr, rankP, size, nameLen
  integer :: dims(2) = (0, 0), coords(2)
  integer :: comm, rankC, column
  character(len=MPI_MAX_PROCESSOR_NAME) :: name
  real(kind=8), allocatable, dimension(:, :) :: arrO, arrN
  integer :: idxL, idxR, idxT, idxB  ! index of neighbor arrays: left, right, top, bottom
  integer status(MPI_STATUS_SIZE)
  logical :: periods(2) = (/.false., .false./)


  call MPI_Init(ierr)
  call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)
  call MPI_Comm_rank(MPI_COMM_WORLD, rankP, ierr)
  call MPI_Get_processor_name(name, nameLen, ierr)

  call MPI_Dims_create(size, 2, dims, ierr)
  call MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, .true., comm, ierr)

  call MPI_Comm_rank(comm, rankC, ierr)

  call MPI_Cart_shift(comm, 0, 1, idxL, idxR, ierr)
  call MPI_Cart_shift(comm, 1, 1, idxB, idxT, ierr)

  call MPI_Cart_get(comm, 2, dims, periods, coords, ierr)

  x = length / dims(1)
  y = length / dims(2)

  if (coords(1) < MOD(length, dims(1))) x = x + 1
  if (coords(2) < MOD(length, dims(2))) y = y + 1

  allocate(arrO(0:x+1, 0:y+1))
  allocate(arrN(0:x+1, 0:y+1))

  call MPI_Type_vector(y+2, 1, x+2, MPI_DOUBLE_PRECISION, column, ierr)
  call MPI_Type_commit(column, ierr)

  arrO = 0.0d0
  arrN = 0.0d0

  ! init boundary conditions
  if (coords(2) == 0) then
    arrO(0:x+1, 0) = 8.0d0
    arrN(0:x+1, 0) = 8.0d0
  end if

  if (coords(2) == dims(2) - 1) then
    arrO(0:x+1, y+1) = 8.0d0
    arrN(0:x+1, y+1) = 8.0d0
  end if

  if (coords(1) == 0) then
    arrO(0, 0:y+1) = 8.0d0
    arrN(0, 0:y+1) = 8.0d0
  end if

  if (coords(1) == dims(1) - 1) then
    arrO(x+1, 0:y+1) = 8.0d0
    arrN(x+1, 0:y+1) = 8.0d0
  end if

  call MPI_Barrier(MPI_COMM_WORLD, ierr)

  ! use Red-Black ordering optimized strategy
  itc = 0
  do itc = 0, itcs, 2
    call MPI_Sendrecv(arrO(1, y), x, MPI_DOUBLE_PRECISION, idxT, 0, arrO(1, 0), &
      x, MPI_DOUBLE_PRECISION, idxB, 0, comm, status, ierr)

    call MPI_Sendrecv(arrO(1, 1), x, MPI_DOUBLE_PRECISION, idxB, 1, arrO(1, y+1), &
      x, MPI_DOUBLE_PRECISION, idxT, 1, comm, status, ierr)

    call MPI_Sendrecv(arrO(x, 1), 1, column, idxR, 0, arrO(0, 1), 1, column, idxL, &
      0, comm, status, ierr)

    call MPI_Sendrecv(arrO(1, 1), 1, column, idxL, 1, arrO(x+1, 1), 1, column, idxR, &
      1, comm, status, ierr)

    do j = 1, y
      do i = 1, x
        arrN(i, j) = (arrO(i - 1, j) + arrO(i + 1, j) + arrO(i, j - 1) + arrO(i, j + 1)) * 0.25d0
      end do
    end do

    call MPI_Sendrecv(arrN(1, y), x, MPI_DOUBLE_PRECISION, idxT, 0, arrN(1, 0), &
      x, MPI_DOUBLE_PRECISION, idxB, 0, comm, status, ierr)

    call MPI_Sendrecv(arrN(1, 1), x, MPI_DOUBLE_PRECISION, idxB, 1, arrN(1, y + 1), &
      x, MPI_DOUBLE_PRECISION, idxT, 1, comm, status, ierr)

    call MPI_Sendrecv(arrN(x, 1), 1, column, idxR, 0, arrN(0, 1), 1, column, idxL, &
      0, comm, status, ierr)

    call MPI_Sendrecv(arrN(1, 1), 1, column, idxL, 1, arrN(x+1, 1), 1, column, idxR, &
      1, comm, status, ierr)

    do j = 1, y
      do i = 1, x
        arrO(i, j) = (arrN(i - 1, j) + arrN(i + 1, j) + arrN(i, j - 1) + arrN(i, j + 1)) * 0.25d0
      end do
    end do
  end do

  call MPI_Barrier(MPI_COMM_WORLD, ierr)

  ! ! print result
  ! if (rankC == 0) then
  !   do j = 0, y+1
  !     do i = 0, x+1
  !       print *, arrO(i, j)
  !     end do
  !   end do
  ! end if

  deallocate(arrO)
  deallocate(arrN)

  call MPI_Finalize(ierr)
end program main
