#pragma once

#include "grid.h"

constexpr int MAX_FNAME_SIZE = 80;

void io_write_output(int &snapshot,
                     int step,
                     float t,
                     Grid& grid,
                     const int ncells,
                     const int nghosts);

