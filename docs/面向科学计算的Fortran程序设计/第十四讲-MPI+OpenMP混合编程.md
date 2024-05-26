# MPI+OpenMP混合编程

## 目录

- [MPI+OpenMP混合编程](#mpiopenmp混合编程)
  - [目录](#目录)
  - [MPI 并行程序涉及的两种基本模式](#mpi-并行程序涉及的两种基本模式)
    - [MPI 对等模式](#mpi-对等模式)
    - [MPI 主从模式](#mpi-主从模式)
  - [程序性能估算](#程序性能估算)
    - [并行加速比与效率](#并行加速比与效率)
    - [Amhdal 定律](#amhdal-定律)
  - [MPI+OpenMP混合并行](#mpiopenmp混合并行)
    - [OpenMP 概述](#openmp-概述)
    - [OpenMP 指令](#openmp-指令)

## MPI 并行程序涉及的两种基本模式

- 对等模式：MPI 程序的各个进程的功能地位相同或相近，所不同的只是处理的对象和操作的数据
- 主从模式：MPI程序的各个进程所起的作用和地位并不相同

### MPI 对等模式

如 Jacobi 迭代过程

### MPI 主从模式

如矩阵向量乘，实现 $c=Ab$：

- 主进程将向量 $b$ 广播给所有的从进程
- 然后将矩阵 $A$ 的各行依次发送给从进程，从进程计算一行和 $b$ 相乘的结果，然后将结果发送给主进程
- 主进程循环向各个从进程发送一行的数据，直到将 $A$ 各行的数据发送完毕
- 一旦主进程将 $A$ 的各行发送完毕，则每收到一个结果就向相应的从进程发送结束标志，从进程接收到结束标志后退出执行，主进程收集完所有的结果后也结束

## 程序性能估算

以矩阵向量乘 $c=Ab$为例，假设矩阵 $A$ 为 $n \times n$ 矩阵，$b$ 为 $n \times 1$向量，$c$ 为 $n\times 1$ 向量。假设每次浮点操作的时间为 $T_{calc}$，每次通信的时间为 $T_{comm}$，则总的计算时间为 $(2n ^ 2 - n)T_{calc}$，总的通信时间为 $(n ^ 2 + n)T_{comm}n^2$。

假设 $T_{calc}=T_{comm}$，则当 $n$ 较小时，通信时间占主要部分，而当 $n$ 较大时，计算时间占主要部分。

考虑另外一种计算场景，$C=AB$，假设矩阵 $A$、$B$、$C$ 均为 $n \times n$ 方阵

<!-- todo -->

### 并行加速比与效率

$$
S_{P} = \frac{T_{S}}{T_{P}}
$$

$$
E_{P} = \frac{S_{P}}{P}
$$

- $S_{P}$：并行加速比
- $E_{P}$：并行效率
- $T_{S}$：串行程序的运行时间（串行程序在并行机单处理器上的执行时间）
- $T_{P}$：并行程序的运行时间（程序并行化后，$P$ 个进程在 $P$ 个处理器的执行时间）

### Amhdal 定律

$$
S = \frac{1}{(1-f_{par})+\frac{f_{par}}{P}}
$$

- $S$：并行加速比
- $P$：进程数（并行的核数）
- $f_{par}$：并行部分所占比例（可并行的部分串行时占用的计算时间的百分比）

## MPI+OpenMP混合并行

### OpenMP 概述

- OpenMP是适用于共享存储体系结构上的一个基于线程的并行编程模型
- OpenMP包含编译制导(Compiler Directive)、运行库(Runtime Library)和环境变量(Environment Variables)
- 已经被大多数计算机硬件和软件厂家所标准化

OpenMP 教程：<https://hpc-tutorials.llnl.gov/openmp/>

```Fortran
! openmp_hello.F90
program parallel_hello
  use omp_lib
  implicit none

  ! ! openmp 依赖注释进行运行，否则会报错
  !$omp parallel
  print *, "hello from process: ", omp_get_thread_num()
  !$omp end parallel
end
```

使用 `-fopenmp` 调用 OpenMP，运行时依赖环境变量：`export OMP_NUM_THREADS=4`

编译运行：

```bash
gfortran -fopenmp openmp_hello.f90
./a.out
```

屏幕输出：

```txt
 hello from process:            0
 hello from process:            1
 hello from process:            2
 hello from process:            3
```

### OpenMP 指令

| ID  |       指令        |                                                    说明                                                    |
| :-: | :---------------: | :--------------------------------------------------------------------------------------------------------: |
|  1  |     parallel      |                            用在一个代码段之前，表示这段代码将被多个线程并行执行                            |
|  2  |        do         |               用于 do 循环之前，将循环分配到多个线程中并行执行，必须保证每次循环之间无相关性               |
|  3  |  **parallel do**  |            parallel和do语句的结合，也是用在一个do循环之前，表示do循环的代码将被多个线程并行执行            |
|  4  |     sections      |                                      用在可能会被并行执行的代码段之前                                      |
|  5  | parallel sections |                                    parallel 和 sections 两个语句的结合                                     |
|  6  |   **critical**    |                                           用在一段代码临界区之前                                           |
|  7  |      single       |                    用在一段只被单个线程执行的代码段之前，表示后面的代码段将被单线程执行                    |
|  8  |      barrier      | 用于并行区内代码的线程同步，所有线程执行到 barrier 时要停止，直到所有线程都执行到 barrier 时才继续往下执行 |
|  9  |      master       |                                       用于指定一段代码块由主线程执行                                       |
| 10  |      ordered      |                                      用于指定并行区域的循环按顺序执行                                      |
| 11  |   threadprivate   |                                        用于指定一个变量是线程私有的                                        |

private 与 shared 子句

```Fortran
!$omp parallel private(priv_var1, priv_var2) shared(shar_var1)
```

- private 子句：用于将一个或多个变量声明成线程私有的变量，指定每个线程都有它自己的变量私有副本，其他线程无法访问该私有副本
- shared 子句：它所列出的变量被线程组中所有的线程共享，所有线程都能对它进行读写访问

firstprivate、lastprivate、reduction子句

- firstprivate子句：private 声明的私有变量不能继承同名变量的值，但实际情况中有时需要继承原有共享变量的值，OpenMP 提供 firstprivate 子句来实现这个功能
- lastprivate 子句：将变量从最后的循环迭代或段复制给原始的变量
- reduction子 句：使用指定的操作对其列表中出现的变量进行规约

```Fortran
!$omp parallel do private(i), lastprivate(x)
do i = 1, 10
  x = i * i
  a(i) = x * b(i)
end do
print *, x
! ^ x has the value 100

!$omp parallel do private(i), reduction(+:sum)
do i = 1, 10
  sum = sum + arr(i)
end do
```

---

与 MPI 操作进程不同，OpenMP 操作线程，因此 OpenMP 的并行区域必须在 MPI 的并行区域内部，即 OpenMP 的并行区域必须在 MPI 的进程中执行。

> **进程与线程**
>
> - 进程是一个程序的实例。每个进程都有一个单独的内存地址空间，这意味着一个进程独立运行，并与其他进程隔离。一台有 N 个内核的机器上最多可以有 N 个进程同时运行
> - 线程是一个进程中的执行单位。一个进程可以只有一个线程，也可以有许多线程，进程中的每个线程都共享该进程的内存和资源
> - OpenMP 所做的是在同一个进程上创建多线程，由于这些线程共享资源，它们可以在分配给一个进程的变量的内存地址上进行读写

混合编程的优点：

1. 节点间 MPI 的可扩展
2. 节点内 OpenMP 的高效率
