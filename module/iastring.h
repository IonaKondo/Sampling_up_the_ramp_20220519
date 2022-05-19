#ifndef IASTRING_H  // Prevent multiple inclusions
#define IASTRING_H

/*****************************************************************************
 *                                                                           *
 *  File          : iastring.h                                               *
 *  Author        : Ian Bond                                                 *
 *  Creation Date : 6/6/2001                                                 *
 *                                                                           *
 *  Definition of infinite array of strings and utility function to          *
 *  decompose a string sentence into individual words. This is quite         *
 *  useful.                                                                  *
 *                                                                           *
 ****************************************************************************/

#include "ia.h"
#include "sstring.h"

// Special typedef of an infinite array of strings
typedef InfiniteArray<String> IAString;

// Decompose a "sentence" into "words"
int string2words(String& sentence, IAString& words);

#endif
