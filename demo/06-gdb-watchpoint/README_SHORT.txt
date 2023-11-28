06 Demo Watchpoint 
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

4	Set a watchpoint at the `sum` variable:

        (gdb) watch sum

5	Run the program using

        (gdb) run

    It should halt each time the value of `sum` has been modified.

6	To watch a memory address/variable, it needs to be in scope. We'll
    now set a watchpoint for `sum2`, which is inside `int main()`.

6.1	Set a breakpoint at line 21 in main.c and run gdb:

        (gdb) main.c:21
        (gdb) run

6.2	When gdb halts now, `sum2` is in scope. Now we can set a watchpoint:

        (gdb) watch sum2

	and run the program:

        (gdb) run

HINT: Try setting a watchpoint with `sum2` being out of scope, e.g. right
after starting up gdb. Get familiar with the error message you'll get.

