#!/bin/bash

# this is just for the demo. This path is valid for Ubuntu 21+.
# It may be different on your operating system and machine.

echo Path on Ubuntu21+ is
echo /var/lib/apport/coredump/
echo Contents of that directory:
ls /var/lib/apport/coredump/
echo

echo 'You may be able to find the location of your core dump directory using the `coredump` command:'
echo '$ coredump'
