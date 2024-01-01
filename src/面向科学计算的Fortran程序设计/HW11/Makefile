FC     = gfortran
FFLAGS = -O0

all: main clean

CalcConvolution.o: CalcConvolution.f90
	$(FC) $(FFLAGS) -c $<

QuickSort.o: QuickSort.f90
	$(FC) $(FFLAGS) -c $<

solution.o: solution.f90
	$(FC) $(FFLAGS) -c $<

main: CalcConvolution.o QuickSort.o solution.o
	$(FC) $(FFLAGS) -o $@ $^

run:
	./main || main.exe

clean:
	rm -f *.o *.mod $(all) || del *.o *.mod $(all)

dev: all run
