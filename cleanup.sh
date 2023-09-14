#!/bin/bash

for dir in ./gdb-FPE ./gdb-basics; do

    cd $dir
    make clean
    cd ..

done

rm `find . -name compile_commands.json`
