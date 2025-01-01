program main
   implicit none
   integer :: n, i, j, k, count = 0
   integer, dimension(:, :, :), allocatable :: arr
   print *, 'Enter the size of the array, and the number should be no more than 100:'
   ! read (*, *) n
   n = 1
   allocate (arr(n, n, n))
   do k = 1, n
      do j = 1, n
         do i = 1, n
            arr(i, j, k) = i*100 + j*10 + k
            if (i + k + j == n) count = count + arr(i, j, k)
         end do
      end do
   end do
   print *, 'The result is:', count
   deallocate (arr)
end program main
