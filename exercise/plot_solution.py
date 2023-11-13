#!/usr/bin/env python3

import numpy as np
from matplotlib import pyplot as plt
import os
import sys

usage = """
plot_solution.py

Plots the solutions of the linear advection outputs. Creates
png images with the same basename as the output data file. E.g.
output_XXXX.dat will be plotted as output_XXXX.png.


Usage:
    plot_solution.py
        plots all output_*.dat files it finds in the current work directory.

    plot_solution.py output_XXXX.dat
        plots only result of file output_XXXX.dat
"""


def remove_python_style_comments(line):
    """
    Remove # if the line starts with it
    """

    if line[0] == "#":
        return line[1:].strip()

    return line


def line_is_empty(line):
    """
    Check whether line contains only spaces and/or newline chars
    """
    clean = line.strip()
    if len(clean) == 0:
        return True
    else:
        return False


def read_output(fname):
    """
    Read the given output file.
    returns:
        x:          location of the cell
        q:          numpy array of the advected quantity
        t:          time of the output
        step:       current step of the simulation
    """

    if not os.path.isfile(fname):
        raise ValueError(f"Given file '{fname}' doesn't exist.")

    f = open(fname)

    t = None
    step = None
    ncells = None

    linecount = 0
    while True:
        # safety measure
        linecount += 1
        if linecount > 1000:
            print("Error: Got to linecount = 1000 without having found all metadata.")
            print("got t:", t)
            print("got step:", step)
            print("got ncells", ncells)
            quit(1)

        line = f.readline()
        clean = remove_python_style_comments(line)
        if line_is_empty(clean):
            continue

        else:
            if clean.strip().startswith("x"):  # header name descriptions
                continue
            name, eq, value = clean.partition("=")
            nstr = name.strip()
            if nstr == "ncells":
                ncells = int(value)
            elif nstr == "t":
                t = float(value)
            elif nstr == "nsteps":
                step = int(value)
            else:
                raise ValueError("Unknown name: '{0}'".format(name))

        if ncells is not None and t is not None and step is not None:
            break

    f.close()

    x, q = np.loadtxt(
        fname,
        usecols=[0, 1],
        dtype=float,
        unpack=True,
        skiprows=linecount,
        delimiter=",",
    )

    if ncells != x.shape[0]:
        print("error: expected and read number of cells not equal.")
        print("Expected:", ncells)
        print("Read in:", x.shape[0])
        quit(1)

    return x, q, t, step


def get_filelist():
    """
    Get the list of files which to plot.

    Returns: filelist
        list of file names to plot.
    """

    # grab cmdline args first
    for helpstring in ["-h", "--h", "--help"]:
        if helpstring in sys.argv:
            print(usage)
            quit()

    filelist = []
    if len(sys.argv) > 1:
        # check cmdline arguments for which files to plot
        for i in range(1, len(sys.argv)):
            arg = sys.argv[i]
            if not os.path.exists(arg):
                print(f"Argument '{arg}' is not an existing file.")
                continue
            if "output_" in arg and arg.endswith(".dat"):
                filelist.append(arg)
            else:
                print(f"Argument '{arg}' doesn't look like a valid output file.")

        if len(filelist) == 0:
            print("No argument provided was a valid file. Stopping now.")
            quit()

    else:
        # find all output files yourself.
        ls = os.listdir()
        for f in ls:
            if f.startswith("output_") and f.endswith(".dat"):
                filelist.append(f)

        if len(filelist) == 0:
            print("Found no output files in current working directory.")
            print("Directory contents are:")
            print(ls)
            print("Stopping now.")
            quit()
        else:
            print("Plotting all output_*.dat files in current workdir.")

    return filelist


def generate_figname(filename):
    """
    Generate the name of the image file to be saved.
    """

    if not filename.endswith(".dat"):
        raise ValueError("I expected a .dat file. But I got", filename)

    return filename[:-3] + "png"


def plot_solution(x, q, t, step, filename):
    """
    Plot the solution and save the figure.

    x: x-coordinates of cells
    q: q-values of cells
    t: current time
    step: current simulation step
    filename: filename of the output file
    """

    fig = plt.figure(figsize=(6, 4))
    ax = fig.add_subplot(111)
    ax.scatter(x, q, s=2, marker=".")

    ax.set_xlabel("$x$", usetex=True)
    ax.set_ylabel("$q(x)$", usetex=True)

    title = "t = {0:12.3e}, step = {1:6d}".format(t, step)
    ax.set_title(title)

    plt.tight_layout()

    figname = generate_figname(filename)
    plt.savefig(figname, dpi=200)
    print("Saved", figname)

    plt.close()

    return


if __name__ == "__main__":

    filelist = get_filelist()

    for f in filelist:
        x, q, t, step = read_output(f)
        plot_solution(x, q, t, step, f)
