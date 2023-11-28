13 Demo Valgrind
==========================

1   Look through the source code of the program.

2   Don't forget to compile with the debug flags! Point them out on the compile
    command. To compile the code, run `make`, or the full compilation command
    manually, e.g.

        $ make

    or

        $ gcc main.c -o ex -g -lm

3   Run the code using

        $ ./ex

    It should execute without a message nor error.
    But by looking through it, we know that it should've had memory errors - an 
    access out of bounds, and memory leaks.


4   Run the code with valgrind:

        $ valgrind ./ex

    Valgrind will produce a lot of output. The important lines are:

        ==275612== Invalid write of size 4
        ==275612==    at 0x109215: main (main.c:19)

    which tells you that you're writing somewhere where you shouldn't be, and even
    tell you where it happened (main.c:19). The other important part is the checks
    for memory leaks:

        =275612== HEAP SUMMARY:
        ==275612==     in use at exit: 400 bytes in 10 blocks
        ==275612==   total heap usage: 11 allocs, 1 frees, 480 bytes allocated

    which tells you that you didn't free 400 bytes in 10 blocks, i.e. 10 allocations.


5   Re-run the code with valgrind with the `--leak-check=full` flag:

        $ valgrind --leak-check=full ./ex

    The "HEAP SUMMARY" should now look something like this:

        ==275688== HEAP SUMMARY:
        ==275688==     in use at exit: 400 bytes in 10 blocks
        ==275688==   total heap usage: 11 allocs, 1 frees, 480 bytes allocated
        ==275688== 
        ==275688== 400 bytes in 10 blocks are definitely lost in loss record 1 of 1
        ==275688==    at 0x4848867: malloc (vg_replace_malloc.c:393)
        ==275688==    by 0x1091C1: main (main.c:11)

    and will now tell you that you allocated memory on main.c:11 which you didn't 
    free later.
