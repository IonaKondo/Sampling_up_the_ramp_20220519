#include "options.h"

OptionSet::OptionSet(void)
{
}

OptionSet::OptionSet(int argc, char *argv[])
{
  parseCommand(argc, argv);
}

void OptionSet::parseCommand(int argc, char *argv[])

  /* Parse the program command line and the parameter file if the
     "-file" argument name is specified. All the hard work is done in
     this function. */
{
  // Start counting the number of command words - this includes
  // argument names and argument parameters
  nwords = 0;

  // First parse the command line
  String filename;
  for (int n = 0; n < argc; ++n) {
    if (strcmp("-file", argv[n]) == 0) {
      filename = argv[n+1];
      //cout << "Load parameter file " << filename << endl;
    }
    wordlist[nwords] = argv[n];
    ++nwords;
  }

  // Gobble up the option/parameter file if one is specified
  if (filename.length() > 0) {

    // Open the file if possible
    ifstream fin;
    fin.open(filename.c_str());
    if (fin.bad()) {
      cout << "Can't open file: " << filename << endl;
      exit(8);
    }
    
    // Read each line in the file
    char line[200];
    while (fin.getline(line, sizeof(line))) {
      
      String sline = line;
      
      // Is the the line "active" - ie uncommented and non-blank
      if (sline[0] != '#' && sline.length() > 0) {
	
	IAString words;
	int nline = string2words(sline, words);

	// The first word of a line in a parameter file is the
	// argument name. So make it a switch
	words[0] = "-" + words[0];

	for (int m = 0; m < nline; ++m) {
	  wordlist[nwords] = words[m];
	  ++nwords;
	}
      }
    }

    fin.close();
  }  

  //for (int i = 0; i < nwords; ++i)
  //cout << wordlist[i] << "/ " << i << endl;
}

int OptionSet::getOption(const String argname, int argno, int def_value)
{
  String svalue = getOption(argname, argno, "");
  if (svalue.length() > 0)
    return atoi(svalue.c_str());
  else
    return def_value;
}

double OptionSet::getOption(const String argname, int argno, double def_value)
{
  String sdef = "";
  String svalue = getOption(argname, argno, "");
  if (svalue.length() > 0)
    return atof(svalue.c_str());
  else
    return def_value;
}

String OptionSet::getOption(const String argname, int argno, String def_value)
{
  int npoint = locate(argname);
  int nvalue = npoint + argno;

  if (nvalue < nwords && npoint > 0)
    return wordlist[nvalue];
  else
    return def_value;
}

bool OptionSet::checkSwitch(const String argname)
{
  if (locate(argname) > 0)
    return true;
  else
    return false;
}

int OptionSet::numArgs(const String argname)

  /* Return the number of parameter arguments associated with the
     argument name. Note that the argument name itself is always the
     first argument. */
{
  int nstart = locate(argname);
  int nargs = nstart + 1;
  while (nargs < nwords && wordlist[nargs][0] != '-') ++nargs;
  return nargs - nstart;
}

int OptionSet::locate(String argname)

  /* Locate the keyword associated with argname. */
{
  String key = "-" + argname;
  int n = 0;
  while (n < nwords && key != wordlist[n]) {
    ++n;
  }

  if (n >= nwords) return -1;

  if (key == wordlist[n]) 
    return n;
  else
    return -1;

  return 0;
}

OptionSet::~OptionSet(void)
{
}
