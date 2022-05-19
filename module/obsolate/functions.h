#ifndef FUNCTIONS_H  /* Prevent multiple inclusions */
#define FUNCTIONS_H

/******************************************************************************
 *                                                                            *
 *  File:          functions.h                                                *
 *  Author:        Ian Bond                                                   *
 *  Date Created:  26/11/1998                                                 *
 *                                                                            *
 *  This module contains implementations for a number of useful               *
 *  mathematical functions and classes used in difference imaging             *
 *  photometry.                                                               *
 *                                                                            *
 *  Modified 23/3/2001 - more streamlined version                             *
 *                                                                            *
 *****************************************************************************/

#include <math.h>
#include "arrays.h"

// Evaluate x^n where n is an integer
double power(double x, int n);

// Evaluate un-normalised gaussian function exp(-x^2/2) 
double gauss(double x);

class P2Dset {

  /* This class maintains and keeps track of all terms in an expanded
     2 dimensional polynomial of given degree. SUM_n (x+y)^n*/

public:

  // Initialise the class simply
  P2Dset(void);

  // Define the polynomial degree
  int define(int degree);

  // Return total number of functions in the set
  int total(void);

  // Return degree of polynomials
  int degree(void);

  // Evaluate nth function at x and y
  double value(double x, double y, int n);

  // Destructor
  ~P2Dset(void);

private:

  // Scale factor
  double Scale;

  // Polynomial degree
  int Degree;

  // Total number of functions in the set
  int numFunctions;

  // table of polynomial indices
  int *indexPoly1, *indexPoly2;
};

class GP2Dset {

  /* This class represents the set of basis functions used in modeling
     the convolution kernel in the difference imaging photometry
     problem. The basis functions are an assortment of gaussian
     functions of selected widths, each modified by a polynomial. The
     degree of the polynomial is specified for each gaussian
     function. Member functions are available to return the value of
     any given function at x and y and linear combinations over all
     basis functions */

public:

  // Construct the class simply
  GP2Dset(void);

  // Define or re-define the number of Gaussians in the set
  void set_gauss(int numgauss);

  // For the given gaussian number, define the shape parameters and
  // the polynomial degree of the modifying polynomial
  void define(double sigma, int degree, int gauss_no);

  // Re-calculate normalisation table
  void renormalize(int halfrange);

  // Generate the table of Gaussian and Polynomial indices
  int implement(void);

  // Return total number of functions in the set
  int total(void);

  // Return information on the Gaussians
  int gauss_num(void);
  void gauss_info(double& sigma, int& degree, int n);

  // Evaluate n'th function at x and y - note that the 2 dimensional
  // function is separable in x and y
  double value_x(double x, int n);
  double value_y(double y, int n);
  double value(double x, double y, int n);
  int is_even(int n);

  // Destroy
  ~GP2Dset(void);

private:

  // Number of Gaussians in the set
  int numGauss;

  // Table of sigmas and polynomial degrees
  int *Degree;
  double *Sigma;

  // Normalisation tables
  double *normal_x, *normal_y;

  // Prefix table: 0 if odd, 1 if even
  int *prefix;

  // Total number of functions in the set
  int numFunctions;

  // Table of Gaussian and polynomial indices
  int *indexGauss;
  int *indexPoly_x;
  int *indexPoly_y;

};

#endif
