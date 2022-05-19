#ifndef SPLINE3_H
#define SPLINE3_H

#include <cmath>
//#include <math.h>
#include <iostream>
#include "arrays.h"

/****************************************************************************
 * One dinemnsional interpolation using cubic splines                       *
 *--------------------------------------------------------------------------*/

typedef float DataType;
//typedef double DataType;

void   spline(VectorD& x, VectorD& y, double yp1, double ypn, VectorD& y2);
double splint(VectorD& xa, VectorD& ya, VectorD& y2a, double x);

/****************************************************************************
 * These routines use low level data arrays rather than my own array        *
 * templates. They may be faster.                                           *
 *--------------------------------------------------------------------------*/

void spline(DataType* x, DataType* y, DataType yp1, DataType ypn, 
	    DataType* y2, int numdata);

DataType splint(DataType* xa, DataType* ya, DataType* y2a, DataType x, 
		int numdata);

#endif
