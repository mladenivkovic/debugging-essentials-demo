#!/bin/bash

# this doesn't work from inside the script, run directly in terminal

echo "$ ulimit -S unlimited"
echo "$ ulimit -c unlimited"
echo "This won't work when run inside the script. You need to run it manually."
