# Set up your compiler and compiler flags here.
# The default is set up for gfortran. You may want to change that.
# Typical compiler names are:
#	gfortran	from the gcc compiler suite
#	ifort		intel classic fortran compiler
#	ifx		intel oneAPI fortran compiler
#	flang		LLVM fortran compiler
#
# if you are working on DINE, you should first load a compiler module.
# Then you should be able to pass the compiler as FCOMP=$(F90)

# try using gfortran as default. Will be overridden if the ${F90}
# variable is defined in your environment.
FC ?= gfortran
F90 ?= $(FC)


# compiler executable name
FCOMP=$(F90)
# FCOMP=gfortran
# FCOMP=ifort
# FCOMP=ifx
# FCOMP=flang

# flags determining optimization
OPTFLAGS= -O3			# aggressive optimization
				# You may want to reduce the optimization lever during debugging.
				# Try -O0, -O1, -O2 for example.
DEBUGFLAGS=			# Flags used for debugging. You'll want to add `-g` here to enable
				# debugging symbols so you can work with gdb.

FORTRANFLAGS= -ffree-line-length-none



# ===============================================================
# You shouldn't need to touch anything below this line.

OBJ= params.o cell.o initial_conditions.o io.o boundary_conditions.o solver.o

all: linear_advection 

boundary_conditions.o: boundary_conditions.f90 params.o cell.o
	$(FCOMP) -c boundary_conditions.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

cell.o: cell.f90 params.o
	$(FCOMP) -c cell.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

initial_conditions.o: initial_conditions.f90 params.o cell.o
	$(FCOMP) -c initial_conditions.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

io.o: io.f90 params.o cell.o
	$(FCOMP) -c io.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

params.o: params.f90
	$(FCOMP) -c params.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

solver.o: solver.f90 cell.o params.o
	$(FCOMP) -c solver.f90 $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS)

linear_advection: linear_advection.f90 $(OBJ)
	$(FCOMP) linear_advection.f90 -o linear_advection $(OPTFLAGS) $(DEBUGFLAGS) $(FORTRANFLAGS) $(OBJ)


.PHONY:
	clean

clean:
	rm -f *.o *.mod linear_advection
