! 串行程序版本，供以参考
program main
  implicit none
  integer :: throw = 28000000, hits = 0, i
  real    :: dist, x2, y2, x, y, ratio, pi

  do i = 1, throw
    call random_number(x)
    call random_number(y)

    x2 = x * x
    y2 = y * y
    dist = sqrt(x2 + y2)

    if (dist .le. 1.0) then
      hits = hits + 1
    endif
  end do

  ratio = real(hits) / real(throw)
  pi = 4.0 * ratio
  write (*, "('the value of pi is calculated to be ', f14.8)") pi
end program main
