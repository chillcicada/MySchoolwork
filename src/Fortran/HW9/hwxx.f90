! 利用Monte Carlo 方法计算圆周率 pi，用户输入进程需要的计算点数 N，利用 bcast 和 reduce 实现圆周率计算
! 随机数生成 RANDOM_NUMBER 函数
program mcpi
   use mpi
   implicit none
   integer :: rank, size, ierr, i, N, cnt, sum
   real    :: x, y, ans

   call MPI_INIT(ierr)
   call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
   call MPI_COMM_SIZE(MPI_COMM_WORLD, size, ierr)

   if (rank == 0) then
      print *, 'Enter the number of points: '
      read *, N
   end if

   call MPI_BCAST(N, 1, MPI_INTEGER, 0, MPI_COMM_WORLD, ierr)

   do i = 1, N/size
      call RANDOM_NUMBER(x)
      call RANDOM_NUMBER(y)
      if (x*x + y*y .le. 1.0) cnt = cnt + 1
   end do

   call MPI_REDUCE(cnt, sum, 1, MPI_INTEGER, MPI_SUM, 0, MPI_COMM_WORLD, ierr)

   if (rank == 0) then
      ans = 4.0*sum/N
      print *, 'Pi is approximately ', ans
   end if

   call MPI_FINALIZE(ierr)
end program mcpi
