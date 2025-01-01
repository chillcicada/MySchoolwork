program main
   implicit none
   character*30 inputRaw
   character*1 temp
   integer counter
   ! counter is used to count the times of loop
   integer*8 :: result1 = 1, result2 = 1
   print '(A)', "Input an string ensure that it's not more than 30 characters:"
   read (*, '(A)') inputRaw
   do counter = 0, len(trim(inputRaw))
      temp = inputRaw(counter:counter + 1)
      select case (temp)
      case ('2')
         ! sad that `case ('2', '3', '4', '5', '6', '7' ,'8', '9')` and `int(temp)` can't pass the compilation
         ! if Fortran type safe ???
         if (result2 <= 100000) then
            result2 = result2*2
            result1 = result2
         else
            result1 = result1*2
         end if
      case ('3')
         if (result2 <= 100000) then
            result2 = result2*3
            result1 = result2
         else
            result1 = result1*3
         end if
      case ('4')
         if (result2 <= 100000) then
            result2 = result2*4
            result1 = result2
         else
            result1 = result1*4
         end if
      case ('5')
         if (result2 <= 100000) then
            result2 = result2*5
            result1 = result2
         else
            result1 = result1*5
         end if
      case ('6')
         if (result2 <= 100000) then
            result2 = result2*6
            result1 = result2
         else
            result1 = result1*6
         end if
      case ('7')
         if (result2 <= 100000) then
            result2 = result2*7
            result1 = result2
         else
            result1 = result1*7
         end if
      case ('8')
         if (result2 <= 100000) then
            result2 = result2*8
            result1 = result2
         else
            result1 = result1*8
         end if
      case ('9')
         if (result2 <= 100000) then
            result2 = result2*9
            result1 = result2
         else
            result1 = result1*9
         end if
      case default
         continue
      end select
   end do
   print *, 'The first product is: ', result1, 'The second product is:', result2
end program main
