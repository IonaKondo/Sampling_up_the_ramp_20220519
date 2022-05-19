#ifndef XTREME_H  /* Prevent multiple inclusions */
#define XTREME_H

/******************************************************************************
 *                                                                            *
 *  File:          xtreme.h                                                   *
 *  Author:        Ian Bond                                                   *
 *  Date Created:  15/ 6/1999                                                 *
 *  Last Modified: 31/ 5/2001                                                 *
 *                                                                            *
 *                                                                            *
 *****************************************************************************/

template<class Type> const Type& maximum(const Type& a, const Type& b)
{
  return (a < b) ? b:a;
}

template<class Type> const Type& minimum(const Type& a, const Type& b)
{
  return (a < b) ? a:b;
}

#endif
