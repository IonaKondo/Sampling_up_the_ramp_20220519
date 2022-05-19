#include "solve.h"

bool lssolve(MatrixD& mx, VectorD& vec)
{
  // All indices start at 1
  int lsize = vec.size();
  int *index = new int[lsize + 1];
  mx.reindex(1, 1);
  vec.reindex(1);

  double d;
  ludcmp(mx, index, d);
  lubksb(mx, index, vec);

  // Re-index back to 0
  mx.reindex(0, 0);
  vec.reindex(0);

  delete[] index;

  return true;
}  

bool ludcmp(MatrixD& a, int *index, double& d)

   /* Implemention of LU decomposition of matrix a as given in NR. */
{
  const double TINY = 1.0e20;

  // MatrixD dimensions
  int nRows, nCols;
  a.size(nRows, nCols);
  if (nRows != nCols) {
    cout << "Not a square matrix in ludcmp " << nRows << " " << nCols << endl;
    return false;
  }

  int n = nRows;

  // Now implement the algorithm

  d = 1.0;

  // Temporary vector
  VectorD vv(n);
  vv.reindex(1);

  int i, j, k;

  for (i = 1; i <= n; ++i) {

    double aamax = 0.0;
    for (j = 1; j <= n; ++j) {
      if (fabs(a(i, j) > aamax)) aamax = fabs(a(i, j));
    }

    if (aamax == 0) {
      cout << "Singular matrix in ludcmp!" << endl;
      return false;
    }
    
    vv(i) = 1.0 / aamax;

  }

  for (j = 1; j <= n; ++j) {

    for (i = 1; i <= j-1; ++i) {
      double sum = a(i, j);
      for (k = 1; k <= i-1; ++k)
	sum -= a(i, k) * a(k, j);
      a(i, j) = sum;
    }

    int imax = 0;
    double aamax = 0.0;

    for (i = j; i <= n; ++i) {

      double sum = a(i, j);
      for (k = 1; k <= j-1; ++k)
	sum -= a(i, k) * a(k, j);
      a(i, j) = sum;

      double dum = vv(i) * fabs(sum);
      if (dum >= aamax) {
	imax = i;
	aamax = dum;
      }
    }

    if (j != imax) {
      for (k = 1; k <= n; ++k) {
	double dum = a(imax, k);
	a(imax, k) = a(j, k);
	a(j, k) = dum;
      }
      d = -d;
      vv(imax) = vv(j);
    }

    index[j] = imax;
    
    if (a(j, j) == 0) a(j, j) = TINY;

    if (j != n) {
      double dum = 1.0 / a(j, j);
      for (i = j+1; i <= n; ++i) 
	a(i, j) = a(i, j) * dum;
    }

  }

  // If the routine has made it this far, it has been successful
  return true;
}

bool lubksb(MatrixD& a, int *index, VectorD& b)

{
  int i, j;

  // MatrixD dimensions
  int nRows, nCols;
  a.size(nRows, nCols);
  if (nRows != nCols) {
    cout << "Not a square matrix in lubksb " << nRows << " " << nCols << endl;
    return false;
  }
  int n = nRows;

  // VectorD dimensions
  nCols = b.size();
  if (nCols != n) {
    cout << "Incompatible vector dimensions in lubksb " << nCols << " " << n << endl;
    return false;
  }

  // Now implement the algorithm
  
  int ii = 0;
  for (i = 1; i <= n; ++i) {

    int ll = index[i];
    double sum = b(ll);
    b(ll) = b(i);
    
    if (ii != 0) {
      for (j = ii; j <= i-1; ++j) sum -= a(i, j) * b(j);
    }
    else if (sum != 0) {
      ii = i;
    }
    
    b(i) = sum;
  }
  
  for (i = n; i >= 1; --i) {
    
    double sum = b(i);
    for (j = i+1; j <= n; ++j) 
      sum -= a(i, j) * b(j);
    
    b(i) = sum / a(i, i);
    
  }

  return true;
}
     
