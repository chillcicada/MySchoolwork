! original_main.F
! 找出并更正该文件中的错误，并用不同的参数输出调试，调试结果以报告形式返回。
! 修改后文件对应 modified_main
      program main
b        this is a homework
         implicit none
         integer a
         integer(kind=7) b
         real*8  c
         real d 
         integer*4 e
         a = 10000000000
10a      d = 55555555.80
         c = a *                   ! c = a * d
     0       d
         b = c
         d = b / (a/10)
         e = b / (a/10)
         print *,'final result is: ',d, e, b
      endprogram
