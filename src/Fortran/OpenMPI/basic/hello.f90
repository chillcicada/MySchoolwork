! 一个简单的 MPI 程序
program main
   use mpi
   implicit none

   integer rank, size, ierr

   call MPI_INIT(ierr)
   call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
   call MPI_COMM_SIZE(MPI_COMM_WORLD, size, ierr)

   write (*, *) "Hello world from process", rank, " of", size

   call MPI_FINALIZE(ierr)
   stop
end program main
