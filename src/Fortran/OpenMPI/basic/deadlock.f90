! 由于无进程发送数据，各进程无法进行，为死锁(deadlock)状态
program main
  use mpi
  implicit none
  integer rank, size, ierr
  integer i, buf(1)
  integer status(MPI_STATUS_SIZE)

  call mpi_init(ierr)
  call mpi_comm_rank(MPI_COMM_WORLD, rank, ierr)  ! 该进程编号
  call mpi_comm_size(MPI_COMM_WORLD, size, ierr)  ! 总进程数目

  buf = 9999
  if(rank == 0) then
    ! recv
    call mpi_recv(buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, status, ierr)
    ! send
    call mpi_send(buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, ierr)
  else
    ! recv
    call mpi_recv(buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, status, ierr)
    ! send
    call mpi_send(buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, ierr)
  end if
  call mpi_finalize(ierr)
  stop
end program main
