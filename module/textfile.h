#ifndef TEXTFILE_H  // Prevent multiple inclusions
#define TEXTFILE_H

/*****************************************************************************
 *                                                                           *
 *  File          : textfile.h                                               *
 *  Author        : Ian Bond                                                 *
 *  Creation Date : 23/8/1999                                                *
 *                                                                           *
 *  Header file for the TextFile class. This is a utility class reading      *
 *  textfiles. The entire file is gobbled up so this may not be suitable     *
 *  for very large textfiles.                                                *
 *                                                                           *
 *  Last modified :  4/6/2001                                                *
 *    - uses my own infinite arrays of strings rather than the "map"         *
 *    class in the STL                                                       *
 *                                                                           *
 *  Bugs                                                                     *
 *    - gets confused if the text file contains strange character sequences  *
 *    like the slash and asterisk                                            *
 *                                                                           *
 ****************************************************************************/

#include <fstream>
//#include <iostream.h>

#include "boolean.h"
#include "iastring.h"

class TextFile {

  /* Class to allow easy parsing of a text file - particularly an
     ascii data table. This was designed with small text files in
     mind. */

public:

  // Constructor
  TextFile(void);

  // Gobble up the whole file
  bool read(String filename);

  int numRecords(void);
  int numWords(int recNo);

  bool getWord(int recNo, int wordNo, String& word);
  bool getWord(int recNo, int wordNo, int& word);
  bool getWord(int recNo, int wordNo, double& word);

  String getWord_str(int recNo, int wordNo);
  int    getWord_int(int recNo, int wordNo);
  double getWord_dbl(int recNo, int wordNo);

  int num_words(int recNo);

  // Destroy
  ~TextFile(void);

private:

  // Number of lines or records in the file
  int NumRecords;

  // Represent each line or record as entry in the following infinite
  // array. Each line entry in the map is decomposed into component
  // words into its own infinite array of strings. Record is in fact a
  // two dimensional infinite array.
  InfiniteArray<IAString> Record;

  // Number of words on each line
  IAint WordCount;

  bool isActive(String line);
};


#endif /* TEXTFILE_H */
