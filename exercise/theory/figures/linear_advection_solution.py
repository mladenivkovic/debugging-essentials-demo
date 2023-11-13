#!/usr/bin/env python3

#-----------------------------------------------------------------
# Create a plot for the Riemann IVP
#-----------------------------------------------------------------


import numpy as np
from matplotlib import pyplot as plt
import matplotlib

params = {
    'axes.labelsize': 12,
    'axes.titlesize': 14,
    'font.size': 16,
    'font.family': 'serif',
    'font.serif': 'DejaVu Sans',
    'legend.fontsize': 12,
    'xtick.labelsize': 10,
    'ytick.labelsize': 10,
    'text.usetex': True,
    'figure.subplot.left'    : 0.05,
    'figure.subplot.right'   : 0.97,
    'figure.subplot.bottom'  : 0.15,
    'figure.subplot.top'     : 0.92,
    'figure.subplot.wspace'  : 0.25,
    'figure.subplot.hspace'  : 0.25,
    'figure.dpi' : 200,
    'lines.markersize' : 6,
    'lines.linewidth' : 2.
}

matplotlib.rcParams.update(params)

fig = plt.figure(figsize=(6, 3))
ax = fig.add_subplot(111)

x = np.linspace(-100, 100., 2000)

def f(x):

    amp1 = 1.
    amp2 = 1.7
    width1 = 2.
    width2 = 3.
    loc1 = 10.
    loc2 = 15.
    exp1 = amp1 * np.exp(-(x - loc1)**2/ width1**2)
    exp2 = amp2 * np.exp(-(x - loc2)**2/ width2**2)

    return exp1 + exp2

a = 10
t1 = 2
t2 = 6

x1 = x + a * t1
x2 = x + a * t2

ax.plot(x, f(x), label=r"$t$ = 0", zorder=4)
ax.plot(x1, f(x), label=r"$t$ = "+str(t1))
ax.plot(x2, f(x), label=r"$t$ = "+str(t2))
ax.set_xlim(0, 100)
ax.legend()
ax.set_yticks([])
ax.set_yticklabels([])
ax.set_xlabel("$x$")
ax.set_ylabel("$q(x, t)$")

#  plt.show()
plt.savefig("linear_advection_solution.pdf")

