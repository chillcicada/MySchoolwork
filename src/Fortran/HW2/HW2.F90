program main
  implicit none
  character(len=39) :: comment = 'The string used for input is the str 1.'
  character(len=3) :: noIndent = '(A)'
  character(len=33) :: inputFormat = '(6X, A13, 11X, I2, 11X, F4.1, 3X)'
  character(len=30) :: outputFormat = '(A, A13, A, I3.3, A, ES9.3, A)'

  character(len=13) name
  integer(kind=1) age
  real(kind=4) weight

  print noIndent, comment
  read (5, inputFormat) name, age, weight
  write (*, outputFormat) 'He said that: "His name is "', name, '". He is ', age, ' years old. His weight is ', weight, ' kg".'
end program main