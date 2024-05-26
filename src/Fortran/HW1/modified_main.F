! modified_main.F
      program main
c        this is a homework
         implicit none
         integer a
         integer(kind=8) b
         real*8  c
         real d 
         integer*4 e
         a = 10000000000
100      d = 55555555.80
         c = a *                   ! c = a * d
     1       d
         b = c
         d = b / (a/10)
         e = b / (a/10)
         print *,'final result is: ',d, e, b
      endprogram
