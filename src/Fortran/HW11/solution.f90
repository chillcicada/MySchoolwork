program main
  use QuickSortModule, only: QuickSort
  ! use NamelistModule
  use CalcConvolutionModule, only: CalcConvolution
  implicit none

  integer, dimension(:), allocatable :: argInt(:)
  real, dimension(:), allocatable    :: argFloat(:)
  integer, parameter :: unit1 = 2023, unit2 = 2024
  character(len=100)  :: fileName
  integer :: maxElements, io, numElements = 0, i
  logical :: alive
  real    :: res

  namelist /input/ fileName, maxElements

  open(unit=unit2, file="input.nml", status='old', action='read')
  read(unit2, nml=input)
  close(unit2)

  allocate(argInt(1:maxElements))
  allocate(argFloat(1:maxElements))

  inquire(file=fileName, exist=alive)
  if (.not. alive) then
    print *, "File ", trim(fileName), " does not exist."
    stop
  end if

  open(unit=unit1, file=filename, status='old', action='read')
  do i = 1, maxElements
    read(unit1, '(F6.2, I8)', iostat=io) argFloat(i), argInt(i)
    if (io /= 0) exit
    numElements = numElements + 1
    ! print *, argFloat(i), argInt(i)
  end do

  maxElements = min(maxElements, numElements)

  call QuickSort(argFloat, 1, maxElements)
  call QuickSort(argInt, 1, maxElements)

  res = CalcConvolution(argInt(1:maxElements),argFloat(1:maxElements))
  print *, "Result: ", res

  open(unit=2025, file='output.txt', status='old', action='write', position='append', form='formatted')
  write(unit=2025, fmt='(A, I8, A, F10.4, A)') '|', maxElements, '|', res, '|'
  close(2025)

  deallocate(argFloat)
  deallocate(argInt)
end program main
