04 Demo for breakpoint with conditional
=============================================

1   Look through the source code of the program.

2   Don't forget to compile with the debug flags! Point them out on the compile
    command. To compile the code, run `make`, or the full compilation command
    manually, e.g.

        $ make

    or

        $ gcc main.c -o ex -g -lm

3   run the program with gdb:

        $ gdb ./ex

4   We now make a *conditional* breakpoint at line 10:

        (gdb) break main.c:10 if i==5

5   Run the program with `run`:

        (gdb) run

    It should run until the breakpoint is hit.

5.1 Verify that the condition is satisfied by printing out `i`:

        (gdb) p i

6   Since this is a C program, we can use the usual C boolean operations.
    For example, our condition could be:

        (gdb) break main.c:10 if i==5 && sum < 25


