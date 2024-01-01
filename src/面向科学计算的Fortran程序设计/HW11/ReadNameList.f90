module NamelistModule
  implicit none

  private
  public :: InputData, ReadNamelist, processInputData

  type InputData
    real    :: data1
    integer :: data2
  end type InputData

contains

  ! subroutine InitNamelist(fileName)
  !   implicit none
  !   character(len=*), intent(in) :: fileName
  ! end subroutine InitNamelist

  subroutine ReadNamelist(fileName, Data, maxElements)
    implicit none
    character(len=*), intent(in) :: fileName
    type(InputData), allocatable, intent(out) :: Data(:)
    integer, intent(out) :: maxElements

    integer :: numElements, i
    real    :: tempData1
    integer :: tempData2
    character(len=100) :: line

    ! 打开 namelist 文件
    open(unit=2023, file=fileName, status='old', action='read')

    ! 读取文件中的数据行数
    numElements = 0
    do
      read(2023, '(A)', iostat=i) line
      if (i /= 0) exit
      numElements = numElements + 1
    end do

    ! 分配数组的大小
    allocate(Data(1:numElements))

    ! 回到文件开头
    rewind(2023)

    ! 读取文件中的数据
    maxElements = numElements
    do i = 1, numElements
      read(line, *) tempData1, tempData2
      Data(i)%data1 = tempData1
      Data(i)%data2 = tempData2
    end do

    ! 关闭文件
    close(2023)
  end subroutine ReadNamelist

  subroutine processInputData(Data, maxElements)
    implicit none
    type(InputData), intent(in) :: Data(:)
    integer, intent(in)         :: maxElements

    integer :: i

    do i = 1, min(size(Data), maxElements)
      ! 处理数据
      print *, "Data1:", Data(i)%data1
      print *, "Data2:", Data(i)%data2
    end do
  end subroutine processInputData
end module

! test
program main
  use NamelistModule
  implicit none

  type(InputData), allocatable :: Data(:)
  integer                      :: maxElements

  call readNamelist('file1.txt', Data, maxElements)
  call processInputData(Data, 5)
  deallocate(Data)
end program main
