#ifndef QUICKSORT_H
#define QUICKSORT_H

/******************************************************************************
*                                                                             *
*    Contains a C++ template implementation of the Quicksort algorithm.       *
*                                                                             *
*    Modified by Ian Bond to include rearrangement of an index table in the   *
*    order as the sort.                                                       *
*                                                                             *
******************************************************************************/

#include "boolean.h"

#ifndef SWAP
#define SWAP
/* template function for interchanging elements A[i] and A[j] of array A[]. */
template <class Type>
void Swap (Type A[], int i, int j)
{
  Type Temp;
  Temp = A[i];
  A[i] = A[j];
  A[j] = Temp;
}
#endif

#ifndef QUICKSORT
#define QUICKSORT
/* template function for performing a Quicksort, sorts array
   A[Left] ... A[Right] into ascending or descending order. If parameter
   upsort == true then A[Left] <= ,,, <= A[Right] and the operator
   < must be defined for the class Type. If parameter upsort == false
   then A[Left] >= ... >= A[Right] and the operator > must be defined for
   the class Type. */
template <class Type>
void QuickSort (Type A[], int Left, int Right, bool upsort = true)
{
  /* This algorithm is described on pg 87 of Kernighan & Ritchie's "The
     C Programming Language" 2nd Edn, Prentice Hall 1988. It was originally
     developed by C.A.R Hoare in 1962. It works by taking a partition element
     (in this case the middle element) and puts all the elements that are
     less then the partition (assuming we are doing an ascending sort) to the
     left of the middle element and all elements equal or greater than the 
     partition to the right of the partition. The subarrays to the right and 
     left of the partition are then sorted by recursively calling QuickSort. 
     The stopping condition for the recursion is when the subarrays have less 
     than two elements. 
     */
  int Index, Last;
  int Mid = (Left + Right) /2;
	
  if (Left >= Right) // do nothing if array contains fewer than two elements
    return;

  // move partition element to A[Left]
  Swap (A, Left, Mid);
  Last = Left;

  // partition
  for (Index = Left +1; Index <= Right; Index++)
    if ( (upsort == true && A[Index] < A[Left]) 
	 || (upsort == false && A[Index] > A[Left]) )
    {
      Swap (A, ++Last, Index);
    }

  // restore partition element
  Swap (A, Left, Last);
  QuickSort (A, Left, Last-1, upsort);
  QuickSort (A, Last+1, Right, upsort);
}

template <class Type>
void QuickIndexSort (Type A[], Type I[], int Left, int Right, 
		     bool upsort = true)
{

  /* This does the same as QuickSort but also re-arranges an index
     table at the same time as the sort. */

  int Index, Last;
  int Mid = (Left + Right) /2;
	
  if (Left >= Right) // do nothing if array contains fewer than two elements
    return;

  // move partition element to A[Left]
  Swap (A, Left, Mid);
  Swap (I, Left, Mid);
  Last = Left;

  // partition
  for (Index = Left +1; Index <= Right; Index++)
    if ( (upsort == true && A[Index] < A[Left]) 
	 || (upsort == false && A[Index] > A[Left]) )
    {
      Swap (A, ++Last, Index);
      Swap (I, Last, Index);
    }

  // restore partition element
  Swap (A, Left, Last);
  Swap (I, Left, Last);
  QuickIndexSort (A, I, Left, Last-1, upsort);
  QuickIndexSort (A, I, Last+1, Right, upsort);
}

#endif // QUICKSORT

#endif // QUICKSORT_H
