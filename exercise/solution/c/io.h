#ifndef IO_H
#define IO_H

#include "cell.h"

#define MAX_FNAME_SIZE 80

void io_write_output(int *snapshot,
                     int step,
                     float t,
                     struct cell* cells,
                     int ncells,
                     int nghosts);

#endif
