#ifndef SOLVE_H
#define SOLVE_H

/****************************************************************************
 * Solution of linear system by LU decomposition                            *
 *--------------------------------------------------------------------------*/

#include <iostream>
#include <cmath>

#include "boolean.h"
#include "arrays.h"

using namespace std;

bool lssolve(MatrixD& mx, VectorD& vec);
bool ludcmp(MatrixD& a, int *index, double& d);
bool lubksb(MatrixD& a, int *index, VectorD& b);

#endif
