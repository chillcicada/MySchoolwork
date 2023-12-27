program main
  implicit none
  ! for output prompt
  character(len=22) :: pmt1 = 'The minimum string is:'
  character(len=30) :: pmt2 = 'The minimum two strings are:'
  character(len=24) :: pmt3 = 'The sorting result is:'
  ! for input
  character(len=30), dimension(:), allocatable :: arr
  integer, dimension(:), allocatable :: stk
  integer :: l = 1, r, lw = 1, hg, idx = 1
  ! `l` means the left index, `r` means the right index
  ! `hg` means the high index, `lw` means the low index
  ! `idx` means the index of `stk`
  character(len=30) :: pvt, tmp
  write (*, '(A)') 'Type an integer to set the length of array:'
  read (*,*) r
  allocate (arr(r), stk(r))
  write (*, '(A)') 'Type the elements of array, space will get ignored:'
  do hg = 1, r
    read (*,*) arr(hg)
  end do
  ! QuickSort, initialize the stk
  if (r > 1) then
    stk(1) = 1
    stk(2) = r
    r = r - 1
    do while (idx > 0)
      hg = stk(idx + 1)
      lw = stk(idx)
      idx = idx - 2
      pvt = arr(hg)
      l = lw
      r = hg - 1
      do
        do while (l < hg .and. arr(l) < pvt)
          l = l + 1
        end do
        do while (r > lw .and. arr(r) > pvt)
          r = r - 1
        end do
        if (l >= r) exit
        ! else swap the left element and right element
        tmp = arr(l)
        arr(l) = arr(r)
        arr(r) = tmp
      end do
      ! swap the pivot and the left element
      arr(hg) = arr(l)
      arr(l) = pvt
      if (l - 1 > lw) then
        idx = idx + 2
        stk(idx) = lw
        stk(idx + 1) = l - 1
      end if
      if (l < hg - 1) then
        idx = idx + 2
        stk(idx) = l + 1
        stk(idx + 1) = hg
      end if
    end do
  end if
  print *, pmt1, trim(arr(1))
  print *, pmt2, arr(1:2)
  print *, pmt3, arr
  deallocate (arr, stk)
end program main
