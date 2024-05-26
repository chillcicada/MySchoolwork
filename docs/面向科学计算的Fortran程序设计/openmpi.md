# OpenMPI Download Tutorial

> the openmpi's official website is [https://www.open-mpi.org/](https://www.open-mpi.org/)

```bash
wget https://download.open-mpi.org/release/open-mpi/v5.0/openmpi-5.0.0.tar.bz2
tar -xvf openmpi-5.0.0.tar.bz2
cd openmpi-5.0.0
./configure
## you can also try to disable the builtin atomics
# ./configure --disable-builtin-atomics
## if you want to install it to a specific directory
## (e.g. /usr/local/openmpi-5.0.0)
# ./configure --prefix=/usr/local/openmpi-5.0.0
## if you want to use a specific compiler (e.g. ifort)
# ./configure CC=icc CXX=icpc FC=ifort F77=ifort
# more information can be found by ./configure --help [| more or less]
## if ./configure run successfully, then
make && make install
```

However, using the openmpi-v5.0.0 can also meet some problems caused by the low version gcc (e.g. gcc-4.8.5). The solution is to use the openmpi-v4.1.6 instead.

```bash
wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.6.tar.bz2
tar -xvf openmpi-4.1.6.tar.bz2
cd openmpi-4.1.6
./configure
make && make install
```

---

Upd： 2024-01-19

openmpi-5.0.0 疑似还有很多 bug（难绷），不过我本机和服务器上没啥问题🤔
