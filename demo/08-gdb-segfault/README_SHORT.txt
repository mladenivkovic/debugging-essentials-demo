08 Demo for gdb segfault
=============================

1   Look through the source code of the program.

2   Don't forget to compile with the debug flags! Point them out on the compile
    command. To compile the code, run `make`, or the full compilation command
    manually, e.g.

        $ make

    or

        $ gcc main.c -o ex -g -lm

3   run the program:

        $ ./ex

    It should crash with a Segfault.

4   run the program with gdb:

        $ gdb ./ex

5   run the program inside gdb:

        (gdb) run

    The program still crashes, but gdb halts the program before it quits.
    You can now inspect the state of the program at the time of the crash. E.g.

        (gdb) p i

    to print out the value of the variable `i`.


