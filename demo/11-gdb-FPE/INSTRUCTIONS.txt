11 Demo to catch FPEs
=================================

1   Look through the source code of the program.

2   Don't forget to compile with the debug flags! Point them out on the compile
    command. To compile the code, run `make`, or the full compilation command
    manually, e.g.

        $ make

    or

        $ gcc main.c -o ex -g -lm

3   run the program:

        $ ./ex

    You should see that for `i` == 800, we divide by zero and get infinity:

         $ ./ex 
           0/1000, val=-0.15432
         100/1000, val=-0.176366
         200/1000, val=-0.20576
         300/1000, val=-0.246912
         400/1000, val=-0.30864
         500/1000, val=-0.41152
         600/1000, val=-0.61728
         700/1000, val=-1.23456
         800/1000, val=inf
         900/1000, val=1.23456

4   Go inside the source code and remove the commented out sections required
    to make floating point exceptions raise an error. Those are lines 4-5:

        /* #define _GNU_SOURCE */
        /* #include <fenv.h> [> Make sure to link with -lm as well <] */

    and line 17:

        /* feenableexcept(FE_DIVBYZERO); */

5   Compile and run the code again. Make sure to use the `-lm` flag.
    When running again, your code should now crash:

         $ ./ex 
           0/1000, val=-0.15432
         100/1000, val=-0.176366
         200/1000, val=-0.20576
         300/1000, val=-0.246912
         400/1000, val=-0.30864
         500/1000, val=-0.41152
         600/1000, val=-0.61728
         700/1000, val=-1.23456
        Floating point exception (core dumped)

6   Re-run the code with gdb now:

        $ gdb ./ex
        (gdb) run

    The program should halt when the FPE is raised. You can now inspect the
    state of the code and find what caused the error.

