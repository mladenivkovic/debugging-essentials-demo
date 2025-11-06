# Set up your compiler and compiler flags here.
# The default is set up for gcc. You may want to change that.
# Typical compiler names are:
#	g++      gnu C compiler
#	icpp     intel classic C compiler
#	icpx     intel oneAPI C compiler
#	clang++  LLVM C compiler
#

# try using g++ as default. Will be overridden if the ${CXX} variable is defined
# in your environment.
CXX ?= g++

# compiler executable name
CPPCOMP=$(CXX)
# CPPCOMP=g++
# CPPCOMP=icpp
# CPPCOMP=icpx
# CPPCOMP=clang++

# flags determining optimization
OPTFLAGS= -O3			# aggressive optimization
				# You may want to reduce the optimization lever during debugging.
				# Try -O0, -O1, -O2 for example.
DEBUGFLAGS=			# Flags used for debugging. You'll want to add `-g` here to enable
				# debugging symbols so you can work with gdb.
CPPFLAGS= -std=c++11


# ===============================================================
# You shouldn't need to touch anything below this line.

OBJ= cell.o grid.o initial_conditions.o io.o solver.o

all: linear_advection

cell.o: cell.cpp cell.h
	$(CPPCOMP) cell.cpp -c $(OPTFLAGS) $(DEBUGFLAGS) $(CPPFLAGS)

grid.o: grid.cpp grid.h
	$(CPPCOMP) grid.cpp -c $(OPTFLAGS) $(DEBUGFLAGS) $(CPPFLAGS)

initial_conditions.o: initial_conditions.cpp cell.h initial_conditions.h
	$(CPPCOMP) initial_conditions.cpp -c $(OPTFLAGS) $(DEBUGFLAGS) $(CPPFLAGS)

io.o: io.cpp cell.h io.h
	$(CPPCOMP) io.cpp -c $(OPTFLAGS) $(DEBUGFLAGS) $(CPPFLAGS)

solver.o: solver.cpp cell.h solver.h
	$(CPPCOMP) solver.cpp -c $(OPTFLAGS) $(DEBUGFLAGS) $(CPPFLAGS)

linear_advection: main.cpp cell.h initial_conditions.h io.h solver.h $(OBJ)
	$(CPPCOMP) main.cpp -o linear_advection $(OPTFLAGS) $(DEBUGFLAGS) $(OBJ) $(CPPFLAGS)

.PHONY:
	clean

clean:
	rm -f *.o linear_advection
