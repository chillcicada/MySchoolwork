module QuickSortModule
  implicit none

  private
  public :: QuickSort

  interface QuickSort
    module procedure QuickSortInt
    module procedure QuickSortReal
  end interface QuickSort

contains
  recursive subroutine QuickSortInt(arr, l, h)
    integer, intent(inout) :: arr(:)
    integer, intent(in)    :: l, h

    integer :: i, j, pvt, tmp

    if (l < h) then
      pvt = arr(l)
      i = l
      j = h

      do while (i < j)
        do while (arr(i) <= pvt .and. i <= h)
          i = i + 1
        end do
        do while (arr(j) > pvt .and. j >= l)
          j = j - 1
        end do
        if (i < j) then
          tmp = arr(i)
          arr(i) = arr(j)
          arr(j) = tmp
        end if
      end do

      tmp = arr(l)
      arr(l) = arr(j)
      arr(j) = tmp

      call QuickSortInt(arr, l, j - 1)
      call QuickSortInt(arr, j + 1, h)
    end if

  end subroutine QuickSortInt

  recursive subroutine QuickSortReal(arr, l, h)
    real, intent(inout) :: arr(:)
    integer, intent(in) :: l, h

    integer :: i, j
    real    :: pvt, tmp

    if (l < h) then
      pvt = arr(l)
      i = l
      j = h

      do while (i < j)
        do while (arr(i) <= pvt .and. i <= h)
          i = i + 1
        end do
        do while (arr(j) > pvt .and. j >= l)
          j = j - 1
        end do
        if (i < j) then
          tmp = arr(i)
          arr(i) = arr(j)
          arr(j) = tmp
        end if
      end do

      tmp = arr(l)
      arr(l) = arr(j)
      arr(j) = tmp

      call QuickSortReal(arr, l, j - 1)
      call QuickSortReal(arr, j + 1, h)
    end if

  end subroutine QuickSortReal

end module QuickSortModule

! ! test
! program main
!   use QuickSortModule, only: QuickSort
!   implicit none

!   integer :: intArray(5) = [5, 3, 1, 4, 2]
!   real    :: realArray(5) = [5.0, 3.0, 1.0, 4.0, 2.0]

!   print *, "input : ", intArray
!   call QuickSort(intArray, 1, 3)
!   print *, "output: ", intArray

!   print *, "input : ", realArray
!   call QuickSort(realArray, 1, size(realArray))
!   print *, "output: ", realArray
! end program main
