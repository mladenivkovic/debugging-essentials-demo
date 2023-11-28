09 GDB Core Dumps
=============================

1   Look through the source code of the program.
    The base program is the same as in exampe 08-gdb-segfault.

2   Don't forget to compile with the debug flags! Point them out on the compile
    command. To compile the code, run `make`, or the full compilation command
    manually, e.g.

        $ make

    or

        $ gcc main.c -o ex -g -lm

3   run the program:

        $ ./ex

    It should crash with a Segfault.

4   Enable core dumps on your machine.

        $ ulimit -S unlimited
        $ ulimit -c unlimited

5   Find out in which directory your system will dump the cores. This may be
    accomplished by running

        $ coredump

    If that doesn't work for you, you'll have to search the internet for 
    answers. For Ubuntu 21+, the location is `/var/lib/apport/coredump/`

5.1 Look at the current contents of the directory.


6   Run the program again:

        $ ./ex

    It should crash with a Segfault again.

6.1 Check your coredump directory. It should now contain a new file.
    Get the full file path and name. We'll need it in the next step.

7   Load the core dump with gdb, and tell gdb which executable was used to
    produce the core dump using

        $ gdb -c /path/to/core/file /path/to/executable

    In our case:

        $ gdb -c /path/to/core/file ./ex

    gdb should now load up the state of your program just as it crashed.

