#ifndef BOOLEAN_H /* prevent multiple inclusions */
#define BOOLEAN_H
/******************************************************************************
*                                                                             *
*   Contains the bool enumeration used to provide Boolean logic.              *
*                                                                             *
******************************************************************************/

/* define NEED_BOOLEAN if C++ implementation doesn't have bool keyword */

/* NEED_BOOLEAN = 0 for g++ ;
   NEED_BOOLEAN = 1 FOR SOLARIS CC */

/* For now manually implement boolean logic */
//#define NEED_BOOLEAN 1
#define NEED_BOOLEAN 0

#if (NEED_BOOLEAN == 1)
  typedef enum {false, true} bool;
#endif

#endif /* BOOLEAN_H */
