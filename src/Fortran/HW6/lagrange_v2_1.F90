module lagrange
   implicit none
   type coordinate
      real*16 :: x, y
   end type coordinate
   real*16, parameter :: pi = 3.14159265358979323846264338327950288d0
   real*16, parameter :: lb = -pi, ub = pi
   integer, parameter :: n = 7
   type(coordinate), dimension(n) :: points

contains
   function func(x)
      real*16, intent(in) :: x
      real*16 :: func
      func = sin(x)*exp(x)
   end function func

   subroutine linspace()
      real*16 :: dx, x
      integer :: i
      dx = (ub - lb)/(n - 1)
      do i = 1, n
         x = lb + (i - 1)*dx
         points(i)%x = x
         points(i)%y = func(x)
      end do
   end subroutine linspace

   function interpolation(x)
      real*16, intent(in) :: x
      real*16 :: interpolation, coefficient
      integer :: i, j, nl
      interpolation = 0.0d0
      if (mod(n, 2) == 0) then
         nl = n/2
      else
         nl = (n - 1)/2
      end if
      if (x > 0.0) then
         do i = n/2, n
            coefficient = 1.0d0
            do j = n/2, n
               if (j /= i) coefficient = coefficient*(x - points(j)%x)/(points(i)%x - points(j)%x)
            end do
            interpolation = interpolation + coefficient*points(i)%y
         end do
      else
         do i = 1, n/2
            coefficient = 1.0d0
            do j = 1, n/2
               if (j /= i) coefficient = coefficient*(x - points(j)%x)/(points(i)%x - points(j)%x)
            end do
            interpolation = interpolation + coefficient*points(i)%y
         end do
      end if
   end function interpolation
end module lagrange

subroutine linspaceX()
   integer, parameter :: length = 100 ! ! step
   real*16, dimension(length) :: axisX
   real*16, parameter :: piX = 3.14159265358979323846264338327950288d0
   real*16, parameter :: lbX = -piX, ubX = piX
   real*16 :: dxX, xX
   integer :: iX
   dxX = (ubX - lbX)/(length - 1)
   do iX = 1, length
      xX = lbX + (iX - 1)*dxX
      axisX(iX) = xX
   end do
end subroutine linspaceX

program main
   use lagrange
   implicit none
   real*16 :: x, y, y0, deviation = 0.0d0
   integer, parameter :: length = 100 ! ! step
   real*16, dimension(length) :: axisX
   integer :: i = 1
   call linspace()
   call linspaceX()
   do i = 1, length
      x = axisX(i)
      ! print *, x
      y = interpolation(x)
      ! print *, y
      y0 = func(x)
      ! print *, y0
      deviation = deviation + abs(y - y0)
   end do
   deviation = deviation/length
   print *, 'The deviation value is', deviation
end program main
