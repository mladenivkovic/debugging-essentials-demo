14 Demo address sanitizer
==========================

1) Compile and run. 
2) Fix out-of-bounds access. Run again.
3) Show memory leak detected.

1   Look through the source code of the program.
    Note that this is the same base program as in demo 13-valgrind.

2   Don't forget to compile with the debug flags!
    To compile the code, run e.g.

        $ gcc main.c -o ex -g -lm

3   Run the code using

        $ ./ex

    It should execute without a message nor error.
    (If you used the makefile, then you compiled with the address sanitizer
    switched on, and the code crashed with an error. You can skip to step 5.)
    But by looking through it, we know that it should've had memory errors - an 
    access out of bounds, and memory leaks.

4   THIS TIME, we also compile with the address sanitizer enabled.
    Remove the executable `./ex` using
        
        $ rm ./ex

    Or by running
        
        $ make clean

    To enable the address sanitizer, we need to pass the compiler the
    corresponding flag.
    That should be the `-fsanitize=address` flag for most compilers.
    
    To compile the code, run `make`, or the full compilation command
    manually, e.g.

        $ make

    or

        $ gcc main.c -o ex -g -lm -fstanitize=address

5   Run the code using

        $ ./ex

    Now the address sanitizer will crash your code with a long error message.

    The first few lines are the important ones:

        ==276278==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x604000000038 at pc 0x55cc417ca337 bp 0x7ffce1fbe420 sp 0x7ffce1fbe410
        WRITE of size 4 at 0x604000000038 thread T0
            #0 0x55cc417ca336 in main /home/mivkov/coding/debugging-essentials-demo/demo/14-address-sanitizer/main.c:19

    It tells you that you've been writing somewhere on the heap where you 
    shouldn't have been.
    More specifically, at line main.c:19

6   Fix the error in the source code, re-compile it, and re-run it.

    It should crash again with a new message, something like

        ==276499==ERROR: LeakSanitizer: detected memory leaks

        Direct leak of 400 byte(s) in 10 object(s) allocated from:
            #0 0x154db70bf91f in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:69
            #1 0x564e92a02261 in main /home/mivkov/coding/debugging-essentials-demo/demo/14-address-sanitizer/main.c:11
            #2 0x154db6c29d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

    If you look closely, you will see that it found that the memory leaks
    stem from memory allocated at main.c:11.


