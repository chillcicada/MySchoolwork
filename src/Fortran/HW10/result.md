| np  | lg  | Time (s) |
| --- | --- | -------- |

mpif90 main.f90 -o main
| 1 | 64 | mpirun -np 1 ./main
0.26 |
| 1 | 128 | mpirun -np 1 ./main
0.24 |
| 1 | 256 | mpirun -np 1 ./main
0.24 |
| 2 | 64 | mpirun -np 2 ./main
0.22 |
| 2 | 128 | mpirun -np 2 ./main
0.23 |
| 2 | 256 | mpirun -np 2 ./main
0.22 |
| 4 | 64 | mpirun -np 4 ./main
0.22 |
| 4 | 128 | mpirun -np 4 ./main
0.22 |
| 4 | 256 | mpirun -np 4 ./main
0.22 |
| 8 | 64 | mpirun -np 8 ./main
0.22 |
| 8 | 128 | mpirun -np 8 ./main
0.23 |
| 8 | 256 | mpirun -np 8 ./main
0.23 |
