#!/bin/bash

mpirun -n 4 xterm -e gdb -ex run ./exMPI
