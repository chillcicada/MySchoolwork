# 调试日志

## 编译过程

### Windows

gcc version 13.1.0

```bash
# cd HW4
gfortran HW4.F90 -g
./a.exe
```

### Linux

使用的 gfortran 和 ifort 为老师服务器版本

```sh
# cd HW4
ifort HW4.F90
# gfortran HW4.F90 -g
./a.out
```

## 调试过程

### 测试用例 1

> 标准输入

输入：

```input
ad253dfs12rtwddf223455s124
```

输出：

```txt
 The first product is:                576000 The second product is:               144000
```

### 测试用例 2

> 含空格输入

输入：

```input
ad253dfs12rt    223455s124
```

输出：

```txt
 The first product is:                576000 The second product is:               144000
```

### 测试用例 3

> 多空格输入

输入：

```input
 a 1 b 2 c 3 d 4 e 5
# 尾端还有一个空格
```

输出：

```txt
 The first product is:                   120 The second product is:                  120
```

### 测试用例 4

> 极端情况，无数字输入

输入：

```input
abcdefghijklmnopqrstuvwxyz
```

> 默认输出初始值 1

输出：

```txt
 The first product is:                     1 The second product is:                    1
```

> 关于判断乘积是否存在的想法：将赋值写到循环中，不过感觉太降低效率了就没这么做。

### 测试用例 5

> 压力测试，全是数字

输入：

```input
999999999999999999999999999999
# 共 30 个 9，理论结果为 42391158275216203514294433201
```

输出：

```txt
 The first product is:  -3535985420588157519 The second product is:               531441
```

> 很不幸，因为 result1 设置的默认位宽为 8，第一个值溢出，但第二个值正常。

#### 解决方案

将 result1 的位宽设置为 16，在 gfortran version 13.1.0 上成功运行

```txt
 The first product is:             42391158275216203514294433201 The second product is:                                   531441
```

> 当然也可以像 C/C++ 一样用字符串模拟高精度运算，不过具体算法我就不写了
