FC = mpif90
FR = mpirun

np ?= 4
lg ?= 64

all: main clean

main:
	$(FC) main.f90 -o main

run:
	$(FR) -np $(np) ./main

clean:
	rm -f main

change:
	sed -i 's/integer, parameter :: length = 64/integer, parameter :: length = $(lg)/g' main.f90
