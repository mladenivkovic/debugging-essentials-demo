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

linear_advection: main.c boundary_conditions.h cell.h initial_conditions.h io.h solver.h
	$(CC) main.c -o linear_advection $(OPTFLAGS) $(DEBUGFLAGS)


clean:
	rm -f *.o linear_advection
