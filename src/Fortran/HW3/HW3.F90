program main
  implicit none
  character (len = 3) :: noIndent = '(A)'
  character (len = 100) str1, str2, str3, temp
  ! temp is used to store the min string temporarily
  ! well it can also read all strings at once, i just make is more readable
  write (*, noIndent) "Enter three strings, and the length of each string is less than 100:"
  write (*, noIndent) "The first string:"
  read (*, noIndent) str1
  write (*, noIndent) "The second string:"
  read (*, noIndent) str2
  if (str1 < str2) then
    temp = str1
    str1 = str2
    str2 = temp
  end if
  write (*, noIndent) "The third string:"
  read (*, noIndent) str3
  if (str1 < str3) then
    temp = str1
    str1 = str3
    str3 = str2
    str2 = temp
  else if (str2 < str3) then
    temp = str2
    str2 = str3
    str3 = temp
  end if
  write (*, noIndent) 'the output is as followed:', trim(str1), trim(str2), trim(str3)
end program main
