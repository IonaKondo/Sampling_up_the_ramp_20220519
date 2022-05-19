#ifndef IA_H  /* Prevent multiple inclusions */
#define IA_H

/******************************************************************************
 *                                                                            *
 *  File:          ia.h                                                       *
 *  Author:        Ian Bond                                                   *
 *  Date Created:  31/5/2001                                                  *
 *                                                                            *
 *  Template definition for infinite array                                    *
 *                                                                            *
 *****************************************************************************/

#include <stdlib.h>
#include <iostream>
using namespace std;

const unsigned int BLOCKSIZE = 10;

template<class Type>class InfiniteArray {

 public:

  // Default constructor and destructor
  InfiniteArray(void);

  // Reset array
  void reset(void);

  // Default destructor
  ~InfiniteArray(void);

  // Return a reference to an element of the array
  Type &operator[] (const unsigned int index);

 private:

  // Highest index currently used
  int maxindex;

  // The data for this block
  Type data[BLOCKSIZE];

  // Pointer to next array
  class InfiniteArray<Type> *next;

};

// Default constructor
template<class Type> 
InfiniteArray<Type>::InfiniteArray(void)
{
  next = NULL;
  memset(data, '\0', sizeof(data));
  maxindex = 0;
}

template<class Type> 
Type &InfiniteArray<Type>::operator [] (const unsigned int index)
{
  // Pointer to the current bucket
  class InfiniteArray<Type> *current_ptr;

  // Index we are working with
  unsigned int current_index;

  // Point to the class we are in now, ie THIS class
  current_ptr = this;
  current_index = index;

  while (current_index >= BLOCKSIZE) {
    if (current_ptr->next == NULL) {
      current_ptr->next = new InfiniteArray;
      if (current_ptr->next == NULL) {
	cerr << "Error: out of memory" << endl;
	exit(8);
      }
    }
    current_ptr = current_ptr->next;
    current_index -= BLOCKSIZE;
  }
  return (current_ptr->data[current_index]);
}

template<class Type> 
void InfiniteArray<Type>::reset(void)  
{
  if (next != NULL) {
    delete next;
    next = NULL;
  }
}

template<class Type> 
InfiniteArray<Type>::~InfiniteArray(void)  
{
  if (next != NULL) {
    delete next;
    next = NULL;
  }
}

// Standard typedefs
typedef InfiniteArray<int> IAint;
typedef InfiniteArray<float> IAfloat;
typedef InfiniteArray<double> IAdouble;

#endif
