# Set up your compiler and compiler flags here.
# The default is set up for gcc. You may want to change that.
# Typical compiler names are:
# 	gcc
# 	icc	 intel C compiler
# 	icx  intel oneAPI C compiler
# 	clang LLVM C compiler
#
# if you are working on DINE, you should first load a compiler module.
# Then you should be able to pass the compiler as CCOMP=$(CC)

# compiler executable name
CCOMP=$(CC) # should work on DINE
# CCOMP=gcc

# flags determining optimization
OPTFLAGS= -O3 	# aggressive optimization
				# You may want to reduce the optimization lever during debugging.
				# Try -O0, -O1, -O2 for example.
DEBUGFLAGS= 	# Flags used for debugging. You'll want to add `-g` here to enable
				# debugging symbols so you can work with gdb.
CFLAGS= -std=c11


# ===============================================================
# You shouldn't need to touch anything below this line.

OBJ= boundary_conditions.o cell.o initial_conditions.o io.o solver.o

all: linear_advection

boundary_conditions.o: boundary_conditions.c boundary_conditions.h cell.h
	$(CCOMP) boundary_conditions.c -c $(OPTFLAGS) $(DEBUGFLAGS) $(CFLAGS)

cell.o: cell.c cell.h
	$(CCOMP) cell.c -c $(OPTFLAGS) $(DEBUGFLAGS) $(CFLAGS)

initial_conditions.o: initial_conditions.c cell.h initial_conditions.h
	$(CCOMP) initial_conditions.c -c $(OPTFLAGS) $(DEBUGFLAGS) $(CFLAGS)

io.o: io.c cell.h io.h
	$(CCOMP) io.c -c $(OPTFLAGS) $(DEBUGFLAGS) $(CFLAGS)

solver.o: solver.c cell.h solver.h
	$(CCOMP) solver.c -c $(OPTFLAGS) $(DEBUGFLAGS) $(CFLAGS)

linear_advection: main.c cell.h initial_conditions.h io.h solver.h $(OBJ)
	$(CCOMP) main.c -o linear_advection $(OPTFLAGS) $(DEBUGFLAGS) $(OBJ) $(CFLAGS)

.PHONY:
	clean

clean:
	rm -f *.o linear_advection
