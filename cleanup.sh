#!/bin/bash

# Do a quick cleanup before the live demo.

cd demo
for dir in gdb-basics gdb-core-dump gdb-FPE gdb-MPI gdb-optimization gdb-segfault valgrind; do

    cd $dir
    echo ===================== $PWD
    make clean
    cd ..

done

cd ..

rm `find . -name compile_commands.json`

