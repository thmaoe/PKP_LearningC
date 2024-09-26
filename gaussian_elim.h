#ifndef GAUSSELIM_H
#define GAUSSELIM_H

#include "constants.h"

void swapRows(int* mat, int r1, int r2); //swap 2 rows of a matrix

int* gaussElim(int *mat); //perform gauss elimination

int* findKernel(int* rref); //find kernel of a matrix given its rref

#endif
