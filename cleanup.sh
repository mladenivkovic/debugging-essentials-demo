#!/bin/bash

# Do a quick cleanup before the live demo.

cd demo
for dir in \
    01-gdb-basics \
    02-gdb-cmdlineargs \
    03-gdb-breakpoint-function \
    04-gdb-breakpoint-conditional \
    05-gdb-reverse \
    06-gdb-watchpoint \
    07-gdb-frames \
    08-gdb-segfault \
    09-gdb-core-dump \
    10-gdb-optimization \
    11-gdb-FPE \
    12-gdb-MPI \
    13-valgrind \
    14-address-sanitizer
do
    cd $dir
    echo ===================== $PWD
    make clean
    cd ..

done

cd ..

rm `find . -name compile_commands.json`

