#include "functions.h"
#include "iostream.h"

// Some utility functions

/*-------------------------------------------------------------------------*/
 
double power(double x, int n) 

  /* Evaluate x^n where n is an integer. */
{
  double value = 1.0;
  for (int i=0; i<n; ++i) value *= x;
  return value;
}

/*-------------------------------------------------------------------------*/
 
double gauss(double x)

  /* Evaluate the un-normalised Gaussian function exp(-x^2/2). */
{
  return exp(-x * x / 2.0);
}

/*****************************************************************************/

P2Dset::P2Dset(void)
{
  Scale = 1000.0;
  indexPoly1 = 0;
  indexPoly2 = 0;
}

/*-------------------------------------------------------------------------*/
 
int P2Dset::define(int degree)

  /* Define the polynomial degree class and generate table of
     polynomial indices. */
{
  Degree = degree;
  numFunctions = (degree + 1) * (degree + 2) / 2;

  // Size up the vector of polynomial indices
  indexPoly1 = new int[numFunctions];
  indexPoly2 = new int[numFunctions];

  // Construct table of indices
  int i, j, index = 0;
  for (i = 0; i <= Degree; ++i)
  for (j = 0; j <= Degree - i; ++j) {
    indexPoly1[index] = i;
    indexPoly2[index] = j;
    ++index;
  }

  return numFunctions;
}

/*-------------------------------------------------------------------------*/
 
int P2Dset::total(void)
{
  return numFunctions;
}

int P2Dset::degree(void)
{
  return Degree;
}

/*-------------------------------------------------------------------------*/
 
double P2Dset::value(double x, double y, int n)

  /* Evaluate n'th function in the class at x and y. */
{
  int iP1 = indexPoly1[n];
  int iP2 = indexPoly2[n];
  return power(x / Scale, iP1) * power(y / Scale, iP2);
}

/*-------------------------------------------------------------------------*/
 
P2Dset::~P2Dset(void)

  /* Destructor. */
{
  delete[] indexPoly1;
  delete[] indexPoly2;
}

/***************************************************************************/

GP2Dset::GP2Dset(void)
{
  Degree = 0;
  Sigma = 0;
  prefix = 0;
  indexGauss = 0;
  indexPoly_x = 0;
  indexPoly_y = 0;
  normal_x = 0;
  normal_y = 0;
}

/*-------------------------------------------------------------------------*/

void GP2Dset::set_gauss(int numgauss)

  /* Define the total number of gaussians in the set. */
{
  numGauss = numgauss;
  Sigma  = new double[numGauss];
  Degree = new int[numGauss];
}

/*-------------------------------------------------------------------------*/
 
void GP2Dset::define(double sigma, int degree, int gauss_no)

  /* Define the polynomial degree and sigma for the given Gaussian
     function number. Each call to this function puts the values in
     the table. */
{
  if (gauss_no >= numGauss) return;
  Degree[gauss_no] = degree;
  Sigma[gauss_no]  = sigma;
}

/*-------------------------------------------------------------------------*/

int GP2Dset::implement(void)

  /* Generate the table of subscript indices. Call this function after
  defining the polynomial degrees and sigmas associated with each
  gaussian. Note: all indices start at 0. */
{
  // Determine total number of basis functions
  numFunctions = 0;
  int n;
  for (n = 0; n < numGauss; ++n) {
    int degree = Degree[n];
    numFunctions += (degree + 1) * (degree + 2) / 2;
  }

  // Size up the index vectors
  indexGauss  = new int[numFunctions];
  indexPoly_x = new int[numFunctions];
  indexPoly_y = new int[numFunctions];

  // Generate table of gaussian and polynomial indices associated with 
  // each individual function in the basis set
  int index = 0;
  for (n = 0; n < numGauss; ++n) {
    int degree = Degree[n];
    for (int i1 = 0; i1 <= degree; ++i1)
    for (int i2 = 0; i2 <= degree - i1; ++i2) {
      indexGauss[index] = n;
      indexPoly_x[index] = i1;
      indexPoly_y[index] = i2;
      ++index;
    }
  }

  // Make prefix table
  prefix = new int[numFunctions];
  prefix[0] = 0;
  for (n = 1; n < numFunctions; ++n) {
    int ipx = indexPoly_x[n];
    int ipy = indexPoly_y[n];
    if ((ipx % 2 == 0) && (ipy % 2 == 0))
      prefix[n] = 1;
    else
      prefix[n] = 0;
  }

  // Normalisation table - initially set to 1
  normal_x = new double[numFunctions];
  normal_y = new double[numFunctions];
  for (n = 0; n < numFunctions; ++n) {
    normal_x[n] = 1.0;
    normal_y[n] = 1.0;
  }

  return numFunctions;
}

/*-------------------------------------------------------------------------*/

void GP2Dset::renormalize(int halfrange)

  /* Regenerate normalisation table based on discrete pixels. */
{
  for (int n = 0; n < numFunctions; ++n) {

    double sumx = 0;
    double sumy = 0;

    for (int i = -halfrange; i <= halfrange; ++i) {
      double arg = i;
      sumx += fabs(value_x(arg, n));
      sumy += fabs(value_y(arg, n));
    }

    normal_x[n] = 1.0 / sumx;
    normal_y[n] = 1.0 / sumy;

  }
}

/*-------------------------------------------------------------------------*/
 
int GP2Dset::total(void)

  /* Return the total number of basis functions in the class. */
{
  return numFunctions;
}

int GP2Dset::gauss_num(void)
{
  return numGauss;
}

void GP2Dset::gauss_info(double& sigma, int& degree, int n)
{
  sigma = Sigma[n];
  degree = Degree[n];
}

/*-------------------------------------------------------------------------*/

double GP2Dset::value_x(double x, int n)
{
  int iG = indexGauss[n];
  int iP = indexPoly_x[n];
  double sigma = Sigma[iG]; 
  return normal_x[n] * power(x, iP) * gauss(x / sigma);
}

/*-------------------------------------------------------------------------*/

double GP2Dset::value_y(double y, int n)
{
  int iG = indexGauss[n];
  int iP = indexPoly_y[n];
  double sigma = Sigma[iG]; 
  return normal_y[n] * power(y, iP) * gauss(y / sigma);
}

/*-------------------------------------------------------------------------*/

double GP2Dset::value(double x, double y, int n)

  /* Return the value of the regular function at x and y given the
     function number. */
{
  double v00 = prefix[n] * value_x(x, 0) * value_y(y, 0);
  return value_x(x, n) * value_y(y, n) - v00;
}

/*-------------------------------------------------------------------------*/

int GP2Dset::is_even(int n)

  /* Returns true if the numbered function has both polynomial
     exponents even and non-zero. */
{
  return prefix[n];
}

/*-------------------------------------------------------------------------*/
 
GP2Dset::~GP2Dset(void)
{
  delete[] Degree;
  delete[] Sigma;
  delete[] prefix;
  delete[] indexGauss;
  delete[] indexPoly_x;
  delete[] indexPoly_y;
  delete[] normal_x;
  delete[] normal_y;
}

