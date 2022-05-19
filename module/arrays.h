#ifndef ARRAYS_H  /* Prevent multiple inclusions */
#define ARRAYS_H

/******************************************************************************
 *                                                                            *
 *  File:          arrays.h                                                   *
 *  Author:        Ian Bond                                                   *
 *  Date Created:  14/ 6/1999                                                 *
 *                                                                            *
 *  Template definitions for arrays of one, two, and three dimensions, namely *
 *  vector, matrix and cube. If you need more than three dimensions you       *
 *  should either re-examine your problem or consider a generalised array     *
 *  class of arbitrary dimension.                                             *
 *                                                                            *
 *  Subscripting is done using (), (,), and (,,) type notation. This is not   *
 *  because I want to make it look like Fortran style subscripting, rather    *
 *  I want it to look like the common notation for vectors and matrices as    *
 *  seen in textbook formulae.                                                *
 *                                                                            *
 *  Last Modified:  30/5/2001                                                 *
 *    - Cube class now deprecated                                             *
 *                                                                            *
 *****************************************************************************/

#include "quicksort.h"

/*****************************************************************************/
/* Template definition for a vector which is a one dimensional array.        */
/*****************************************************************************/
  
template<class Type>class Vector {

public:

  // Constructors
  Vector(void);
  Vector(int size);

  // Set or query the first index subscript of the array
  void reindex(int value);
  int index(void);

  // Resize the vector or get its current size
  void resize(int size);
  int size(void);

  // Reset all elements to the given value
  void reset(Type value);

  // Median of the values in the array
  Type median(void);

  // Subscripting operators to access elements of the vector
  Type  operator()(int n) const;
  Type& operator()(int n);

  // Destructor
  ~Vector(void);

private:

  // Value of first subscript of the array
  int index0;

  // Total number of elements in the array
  int numElements;

  // Buffer to hold the array elements
  Type *buffer;

};

// Default constructor
template<class Type> 
Vector<Type>::Vector(void) : buffer(0)
{
  index0 = 0;
  numElements = 0;
}

// Constructor given vector size
template<class Type> 
Vector<Type>::Vector(int size) : buffer(0)
{
  index0 = 0;
  resize(size);
}

// Re-define the size of the vector - all previous elements are deleted
template<class Type> 
void Vector<Type>::resize(int size)
{
  delete[] buffer;
  numElements = size;
  buffer = new Type[numElements];
}

// Return the current size of the vector
template<class Type> 
int Vector<Type>::size(void)
{
  return numElements;
}

// Define the first subscript
template<class Type> 
void Vector<Type>::reindex(int value)
{
  index0 = value;
}

// Return the value of the first subscript
template<class Type> 
int Vector<Type>::index(void)
{
  return index0;
}

// Reset the values of each element
template<class Type> 
void Vector<Type>::reset(Type value)
{
  for (int n = 0; n < numElements; ++n) buffer[n] = value;
}

template<class Type> 
Type Vector<Type>::median(void)

  /* Return the median element after sorting the array. */
{
  QuickSort(buffer, 0, numElements - 1, true);
  if (numElements == 0) {
    return 0;
  } 
  else if (numElements % 2 == 0) {
    int mid2 = numElements / 2;
    int mid1 = mid2 - 1;
    return (buffer[mid1] + buffer[mid2]) / 2;
  }
  else if (numElements % 2 == 1) {
    int mid = (numElements - 1) / 2;
    return buffer[mid];
  }
  return 0;
}

// Element access
template<class Type> 
Type& Vector<Type>::operator()(int n)
{
  return buffer[n - index0];
}

template<class Type> 
Type Vector<Type>::operator()(int n) const
{
  return buffer[n - index0];
}

template<class Type> 
Vector<Type>::~Vector(void)
{
  delete[] buffer;
}

/*****************************************************************************/
/* Template definition for a matrix                                          */
/*****************************************************************************/

template<class Type>class Matrix {

public:

  // Constructors
  Matrix(void);
  Matrix(int nrows, int ncolumns);

  // Set or query the matrix dimensions
  void resize(int nrows, int ncolumns);
  void size(int& nrows, int& ncolumns);

  // Set or query the first subscript indices
  void reindex(int value_r, int value_c);
  void index(int& value_r, int& value_c);

  // Re-set all elements to the given value
  void reset(Type value);

  // Functions to access elements of the matrix
  Type& operator() (int row, int col);
  Type operator() (int row, int col) const;

  // Destructor
  ~Matrix(void);

private:

  // First subscripts
  int row0, col0;

  // Number of rows and columns
  int numRows, numColumns;

  // Represent matrix as an array of rows - each row being a Vector
  Vector<Type> *buffer;

};

// Default constructor
template<class Type> 
Matrix<Type>::Matrix(void) : buffer(0)
{
  row0 = 0;
  col0 = 0;
}  

// Constructor given size of matrix
template<class Type> 
Matrix<Type>::Matrix(int nrows, int ncolumns) : buffer(0)
{
  row0 = 0;
  col0 = 0;
  resize(nrows, ncolumns);
}

// Re-size the matrix - previous content is deleted
template<class Type> 
void Matrix<Type>::resize(int nrows, int ncolumns)
{
  numRows    = nrows;
  numColumns = ncolumns;

  delete[] buffer;

  buffer = new Vector<Type>[numRows];
  for (int n = 0; n < numRows; ++n) {
    buffer[n].resize(numColumns);
  }
}

// Get the current dimensions of the matrix
template<class Type> 
void Matrix<Type>::size(int& nrows, int& ncolumns)
{
  nrows = numRows;
  ncolumns = numColumns;
}

// Define the first subscript
template<class Type> 
void Matrix<Type>::reindex(int value_r, int value_c)
{
  row0 = value_r;
  col0 = value_c;
  for (int n = 0; n < numRows; ++n) 
    buffer[n].reindex(col0);
}

// Return the value of the first subscript
template<class Type> 
void Matrix<Type>::index(int& value_r, int& value_c)
{
  value_r = row0;
  value_c = col0;
}

template<class Type> 
void Matrix<Type>::reset(Type value)
{
  for (int n = 0; n < numRows; ++n) 
    buffer[n].reset(value);
}

// Functions to access elements of the matrix
template<class Type> 
Type& Matrix<Type>::operator() (int row, int col) {
  return buffer[row - row0](col);
}
  
template<class Type>
Type Matrix<Type>::operator() (int row, int col) const {
  return buffer[row - row0](col);
}

template<class Type> 
Matrix<Type>::~Matrix(void)
{
  delete[] buffer;
}


// Type definitions
typedef Vector<double> VectorD;
typedef Vector<int> VectorI;
typedef Vector<short> VectorS;

typedef Matrix<double> MatrixD;
typedef Matrix<int> MatrixI;
typedef Matrix<short> MatrixS;

#endif /* ARRAYS_H */
