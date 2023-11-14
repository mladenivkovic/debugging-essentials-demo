#!/bin/bash

# exit on error
set -e

make
./linear_advection
python3 ../../plot_solution.py
# eog *png
