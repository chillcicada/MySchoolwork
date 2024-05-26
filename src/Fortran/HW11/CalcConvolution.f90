module CalcConvolutionModule
  implicit none

  private :: HomoCheck
  public  :: CalcConvolution

contains
  function HomoCheck(argInt, argFloat) result(res)
    integer, intent(in) :: argInt(:)
    real, intent(in)    :: argFloat(:)
    logical             :: res

    res = size(argInt) == size(argFloat)
  end function HomoCheck

  function CalcConvolution(argInt, argFloat) result(res)
    integer, intent(in) :: argInt(:)
    real, intent(in)    :: argFloat(:)
    real                :: res

    character(len=44)   :: ErrMsg = "Error: argInt and argFloat must be same size"
    integer             :: i

    if (.not. HomoCheck(argInt, argFloat)) then
      print *, ErrMsg
      stop
    end if

    res = 0.0
    do i = 1, size(argInt)
      res = res + argInt(i) * argFloat(i)
    end do
  end function CalcConvolution
end module CalcConvolutionModule

! ! test
! program main
!   use CalcConvolutionModule, only: CalcConvolution
!   implicit none

!   real    :: result
!   integer :: a(3) = [1, 2 ,3]
!   real    :: b(4) = [1.0, 2.0, 3.0, 4.0]

!   result = CalcConvolution(a(1:2), b(1:2))
!   print *, result
! end program main
