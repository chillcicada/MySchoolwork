! 无进程接收数据，数据存入缓存区，可能造成内存泄漏问题
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
   if (rank == 0) then
      ! send
      call mpi_send(buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, ierr)
      ! recv
      call mpi_recv(buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, status, ierr)
      print *, "Process", rank, "receive ", buf, " from Process 1."
   else
      ! send
      call mpi_send(buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, ierr)
      ! recv
      call mpi_recv(buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, status, ierr)
      print *, "Process", rank, "receive ", buf, " from Process 0."
   end if
   call mpi_finalize(ierr)
   stop
end program main
