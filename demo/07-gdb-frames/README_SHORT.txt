07 Demo GDB Frames Navigation
==============================

1   Look through the source code of the program.

2   Don't forget to compile with the debug flags! Point them out on the compile
    command. To compile the code, run `make`, or the full compilation command
    manually, e.g.

        $ make

    or

        $ gcc main.c -o ex -g -lm

3   run the program with gdb:

        $ gdb ./ex

4   We now make a breakpoint at line 6:

        (gdb) break main.c:6

5   Run the code with gdb:

        (gdb) run

6   When it hits the breakpoint, look at the backtrace using `bt` (or 
    `backtrace`):

        (gdb) bt

    You should see something like

        (gdb) bt
        #0  level_5 (a=11) at main.c:6
        #1  0x000055555555519a in level_4 (a=11) at main.c:11
        #2  0x00005555555551b9 in level_3 (a=7) at main.c:15
        #3  0x00005555555551d8 in level_2 (a=4) at main.c:19
        #4  0x00005555555551f7 in level_1 (a=2) at main.c:23
        #5  0x0000555555555212 in level_0 (a=1) at main.c:27
        #6  0x0000555555555231 in main () at main.c:34

7   Each item of the stack has a number - a so called "frame number."
    You can switch between frames of the stack using the number.
    For example

        (gdb) frame 4

    Puts you back in frame 4, at main.c line 23.
    You can now inspect the scope of that frame. For example, the
    value of the variable `a` is different for each frame in this program.



