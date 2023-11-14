# Set up your compiler and compiler flags here.
# The default is set up for gcc. You may want to change that.
# Typical compiler names are:
# 	gcc
# 	icc	 intel C compiler
# 	icx  intel oneAPI C compiler
# 	clang LLVM C compiler

# compiler executable name
CC=gcc

# flags determining optimization
OPTFLAGS= -O3 	# aggressive optimization
				# You may want to reduce the optimization lever during debugging.
				# Try -O0, -O1, -O2 for example.
DEBUGFLAGS= 	# Flags used for debugging. You'll want to add `-g` here to enable
				# debugging symbols so you can work with gdb.



# ===============================================================
# You shouldn't need to touch anything below this line.

OBJ= boundary_conditions.o cell.o initial_conditions.o io.o solver.o

all: linear_advection

boundary_conditions.o: boundary_conditions.c boundary_conditions.h cell.h
	$(CC) boundary_conditions.c -c $(OPTFLAGS) $(DEBUGFLAGS)

cell.o: cell.c cell.h
	$(CC) cell.c -c $(OPTFLAGS) $(DEBUGFLAGS)

initial_conditions.o: initial_conditions.c cell.h initial_conditions.h
	$(CC) initial_conditions.c -c $(OPTFLAGS) $(DEBUGFLAGS)

io.o: io.c cell.h io.h
	$(CC) io.c -c $(OPTFLAGS) $(DEBUGFLAGS)

solver.o: solver.c cell.h solver.h
	$(CC) solver.c -c $(OPTFLAGS) $(DEBUGFLAGS)

linear_advection: main.c cell.h initial_conditions.h io.h solver.h $(OBJ)
	$(CC) main.c -o linear_advection $(OPTFLAGS) $(DEBUGFLAGS) $(OBJ)

.PHONY:
	clean

clean:
	rm -f *.o linear_advection
