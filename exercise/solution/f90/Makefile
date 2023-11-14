# Set up your compiler and compiler flags here.
# The default is set up for gfortran. You may want to change that.
# Typical compiler names are:
# 	gfortran	from the gcc compiler suite
# 	ifort	 	intel fortran compiler
# 	ifx  		intel oneAPI fortran compiler

# compiler executable name
F90=gfortran

# flags determining optimization
OPTFLAGS= -O3 	# aggressive optimization
				# You may want to reduce the optimization lever during debugging.
				# Try -O0, -O1, -O2 for example.
DEBUGFLAGS= 	# Flags used for debugging. You'll want to add `-g` here to enable
				# debugging symbols so you can work with gdb.

FORTRANFLAGS= -ffree-line-length-none



# ===============================================================
# You shouldn't need to touch anything below this line.

OBJ= params.o cell.o initial_conditions.o io.o boundary_conditions.o solver.o

all: linear_advection 

boundary_conditions.o: boundary_conditions.f90 params.o cell.o
	$(F90) -c boundary_conditions.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

cell.o: cell.f90 params.o
	$(F90) -c cell.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

initial_conditions.o: initial_conditions.f90 params.o cell.o
	$(F90) -c initial_conditions.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

io.o: io.f90 params.o cell.o
	$(F90) -c io.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

params.o: params.f90
	$(F90) -c params.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

solver.o: solver.f90 cell.o params.o
	$(F90) -c solver.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

linear_advection: linear_advection.f90 $(OBJ)
	$(F90) linear_advection.f90 -o linear_advection $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS) $(OBJ)


.PHONY:
	clean

clean:
	rm -f *.o *.mod linear_advection
