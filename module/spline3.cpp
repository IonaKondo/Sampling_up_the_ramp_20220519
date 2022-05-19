/****************************************************************************
 *                                                                          *
 *  Routines for interpolation using cubic splines                          *
 *                                                                          *
 *  All array indices must start at 1                                       *
 *                                                                          *
 *                                                                          *
 ****************************************************************************/

#include "spline3.h"

using namespace std;

void spline(VectorD& x, VectorD& y, double yp1, double ypn, VectorD& y2)

  /* Generate second derivative table. */

{
  int n = x.size();

  y2.resize(n);
  y2.reindex(1);

  x.reindex(1);
  y.reindex(1);

  VectorD u(n);
  u.reindex(1);

  if (yp1 > 0.99e30) {
    y2(1) = 0;
    u(1) = 0;
  }
  else {
    y2(1) = -0.5;
    u(1) = (3.0 / (x(2) - x(1))) * ((y(2) - y(1)) / (x(2) - x(1)) - yp1);
  }

  for (int i = 2; i <= n - 1; ++i) {
    double sig = (x(i) - x(i-1)) / (x(i+1) - x(i-1));
    double p = sig * y2(i-1) + 2;
    y2(i) = (sig - 1.0) / p;
    u(i) = (6.0 * ((y(i+1) - y(i)) / (x(i+1) - x(i)) - (y(i) - y(i-1)) / (x(i) - x(i-1))) / (x(i+1) - x(i-1)) - sig * u(i-1)) / p;
  }

  double qn, un;
  if (ypn > 0.99e30) {
    qn = 0;
    un = 0;
  }
  else {
    qn = 0.5;
    un = (3.0 / (x(n) - x(n-1))) * (ypn - (y(n) - y(n-1)) / (x(n) - x(n-1)));
  }

  y2(n) = (un - qn * u(n-1)) / (qn * y2(n-1) + 1.0);
  for (int k = n-1; k >= 1; --k)
    y2(k) = y2(k) * y2(k+1) + u(k);

  y2.reindex(0);
  x.reindex(0);
  y.reindex(0);

  return;
}

double splint(VectorD& xa, VectorD& ya, VectorD& y2a, double x)

  /* Cubic spline interpolation. */
{
  xa.reindex(1);
  ya.reindex(1);
  y2a.reindex(1);

  int n = xa.size();

  int klo = 1;
  int khi = n;
  while (khi - klo > 1) {
    int k = (khi + klo) / 2;
    if (xa(k) > x) 
      khi = k;
    else
      klo = k;
  }

  double h = xa(khi) - xa(klo);
  if (h == 0)
    cout << "Bad xa input in splint - the xa's must be distinct!!!" << endl;

  double a = (xa(khi) - x) / h;
  double b = (x - xa(klo)) / h;
  double y = a * ya(klo) + b * ya(khi) +
    ((a*a*a - a) * y2a(klo) + (b*b*b - b) * y2a(khi)) * (h*h) / 6.0;

  xa.reindex(0);
  ya.reindex(0);
  y2a.reindex(0);

  return y;
}

/****************************************************************************
 * These routines use low level data arrays rather than my own array        *
 * templates. They may be faster.                                           *
 *--------------------------------------------------------------------------*/ 

void spline(DataType* x, DataType* y, DataType yp1, DataType ypn, DataType* y2,
	    int numdata)

  /* Generate second derivative table. */

{
  int n = numdata;

  DataType *u = new DataType[numdata];

  if (yp1 > 0.99e30) {
    y2[0] = 0;
    u[0] = 0;
  }
  else {
    y2[0] = -0.5;
    u[0] = (3.0 / (x[1] - x[0])) * ((y[1] - y[0]) / (x[1] - x[0]) - yp1);
  }

  for (int i = 1; i <= n - 2; ++i) {
    DataType sig = (x[i] - x[i-1]) / (x[i+1] - x[i-1]);
    DataType p = sig * y2[i-1] + 2;
    y2[i] = (sig - 1.0) / p;
    u[i] = (6.0 * ((y[i+1] - y[i]) / (x[i+1] - x[i]) - (y[i] - y[i-1]) / 
		   (x[i] - x[i-1])) / (x[i+1] - x[i-1]) - sig * u[i-1]) / p;
  }

  DataType qn, un;
  if (ypn > 0.99e30) {
    qn = 0;
    un = 0;
  }
  else {
    qn = 0.5;
    un = (3.0 / (x[n-1] - x[n-2])) * 
      (ypn - (y[n-1] - y[n-2]) / (x[n-1] - x[n-2]));
  }

  y2[n-1] = (un - qn * u[n-2]) / (qn * y2[n-2] + 1.0);
  for (int k = n-2; k >= 0; --k)
    y2[k] = y2[k] * y2[k+1] + u[k];

  delete[] u;

  return;
}

DataType splint(DataType* xa, DataType* ya, DataType* y2a, DataType x, 
		int numdata)

  /* Cubic spline interpolation. */
{
  int n = numdata;

  int klo = 0;
  int khi = n-1;
  while (khi - klo > 1) {
    int k = (khi + klo) / 2;
    if (xa[k] > x) 
      khi = k;
    else
      klo = k;
  }

  DataType h = xa[khi] - xa[klo];
  if (h == 0)
    cout << "Bad xa input in splint - the xa's must be distinct!!!" << endl;

  DataType a = (xa[khi] - x) / h;
  DataType b = (x - xa[klo]) / h;
  DataType y = a * ya[klo] + b * ya[khi] +
    ((a*a*a - a) * y2a[klo] + (b*b*b - b) * y2a[khi]) * (h*h) / 6.0;

  return y;
}

