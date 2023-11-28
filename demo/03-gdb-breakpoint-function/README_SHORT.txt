03 - Set breakpoint at a function
=====================================

Particularly useful if you have a function to handle exits, errors, panics etc
in your program.

1   Look at the program. We call the function `error_exit()` when an "error"
    occurs, i.e. when some condition is satisfied.
    We don't want to guess which parent function call causes the error. We want
    gdb to halt when the error is detected.
    For that, we make a breakpoint on the `error_exit()` function call.

2   Compile the program:

        $ make

    or

        $ gcc main.c -o ex -g -lm

3   Run the program with gdb:

        $ gdb ./ex

4   Make a breakpoint on the function `error_exit()`:

        (gdb) break error.h:error_exit

5   run the program inside gdb using `run`:

        (gdb) run

    gdb should now halt when the function `error_exit()` is called.

