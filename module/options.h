#ifndef OPTIONS_H
#define OPTIONS_H

/******************************************************************************
 *                                                                            *
 *  Utility class for parsing command lines and parameter files.              *
 *                                                                            *
 *  Ian Bond,  24/3/2001                                                      *
 *                                                                            *
 *  Features:                                                                 *
 *    - an argument on the command line will override the same argument if    *
 *    it is present in a parameter file.                                      *
 *                                                                            *
 *  To do:                                                                    *
 *    - improve error checking for cases of bad command specifications        *
 *                                                                            *
 *****************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctype.h>

#include "sstring.h"
#include "iastring.h"

class OptionSet {

public:
  
  // Constructor
  OptionSet(void);
  OptionSet(int argc, char *argv[]);

  // Read all arguments on the command line
  void parseCommand(int argc, char *argv[]);

  // Return value associated with argument
  int    getOption(const String argname, int argno, int    def_value);
  double getOption(const String argname, int argno, double def_value);
  String getOption(const String argname, int argno, String def_value);

  bool checkSwitch(const String argname);
  int  numArgs(const String argname);

  // Destroy
  ~OptionSet(void);

private:

  // Total number of words in the command sequence - this includes
  // argument names and argument parameters
  int nwords;

  // Put all words in this infinite array of strings
  IAString wordlist;

  int locate(String argname);

};

#endif
