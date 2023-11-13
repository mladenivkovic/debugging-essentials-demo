#!/usr/bin/env python3

# -----------------------------------------------------------------
# Draw a plot representing the piecewise constant discretization
# -----------------------------------------------------------------

import numpy as np
from matplotlib import pyplot as plt
import matplotlib.patches as patches


xmin = 0
xmax = 10
ymin = 0
ymax = 4
dx = 3


# some continuous nice looking function to draw
def f(x):
    return 2.0 + 1.3 * np.sin(x) * np.exp(-x / 10)


def integral_f(x):
    return (
        2.0 * x
        - 1.28713 * np.exp(-0.1 * x) * np.cos(x)
        - 0.128713 * np.exp(-0.1 * x) * np.sin(x)
    )


fig = plt.figure(figsize=(9, 4.5))
ax = fig.add_subplot(111, aspect="equal")
ax.set_xlim(xmin, xmax)
ax.set_ylim(ymin, ymax)

ax.set_xticks([])
ax.set_yticks([])

# draw function
x = np.linspace(xmin, xmax, 500)
ax.plot(x, f(x), lw=2, color="k")

x = xmin
while x < xmax:
    # draw rectangle
    height = (integral_f(x + dx) - integral_f(x)) / dx
    ax.add_patch(
        patches.Rectangle((x, ymin), dx, height, fill=True, facecolor="darkgrey")
    )

    # draw red line
    ax.plot([x, x + dx], [height, height], color="r")

    x += dx
    # draw grid
    ax.plot([x, x], [ymin, ymax], ":", color="grey")

plt.subplots_adjust(left=0.05, bottom=0.05, right=0.95, top=1., hspace=0, wspace=0)

# annotate
plt.figtext(0.175, 0.1, r"$i-1$", usetex=True, fontsize=14, horizontalalignment="center")
plt.figtext(0.450, 0.1, r"$i$", usetex=True, fontsize=14, horizontalalignment="center")
plt.figtext(0.725, 0.1, r"$i+1$", usetex=True, fontsize=14, horizontalalignment="center")
plt.figtext(0.175, 0.3, r"$q_{i-1}$", usetex=True, fontsize=14, horizontalalignment="center")
plt.figtext(0.450, 0.3, r"$q_{i}$", usetex=True, fontsize=14, horizontalalignment="center")
plt.figtext(0.725, 0.3, r"$q_{i+1}$", usetex=True, fontsize=14, horizontalalignment="center")
plt.figtext(0.01, 0.5, r"$q(x)$", usetex=True, fontsize=14)
plt.figtext(0.97, 0.16, r"$x$", usetex=True, fontsize=14)

plt.savefig("piecewise_const.pdf")
