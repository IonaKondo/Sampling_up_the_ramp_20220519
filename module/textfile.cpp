#include "textfile.h"

TextFile::TextFile(void)

  /* Initialise the class with the expected (or maximum) number of
     active records in the file and the expected (or maximum length of
     each record. */
{
  NumRecords = 0;
}

bool TextFile::read(String filename)

  /* Read the given filename and load all active (ie non-commented)
     records into the class. */
{
  ifstream fin(filename.c_str());
  if (!fin) {
//    cout << "Couldn't open " << filename.c_str() << endl;
    return false;
  }

  char ch;
  String line;

  int recNo = 0;

  // Read the textfile character by character
  while (fin.get(ch)) {
    
    // Check for end of current line
    if (ch == '\n') {

      // Load words from this line if it is uncommented
      if (isActive(line)) {
	WordCount[recNo] = string2words(line, Record[recNo]);
	++recNo;
      }
      line = "";
    }

    // Otherwise append character onto current line
    else
      line = line + ch;

  }
  
  NumRecords = recNo;
  fin.close();
  return true;
}

int TextFile::numRecords(void)

  /* Return the number of used records. */
{
  return NumRecords;
}

int TextFile::numWords(int recNo)

  /* Return the number of words in the given record number. */
{
  return WordCount[recNo];
}

bool TextFile::getWord(int recNo, int wordNo, String& word)

  /* Extract the given word number from the given record number. */
{
  if (recNo < NumRecords && wordNo < WordCount[recNo]) {
    word = Record[recNo][wordNo];
    return true;
  }
  else
    return false;
}

bool TextFile::getWord(int recNo, int wordNo, int& value)

  /* Extract integer valued word. */
{
  String strvalue;
  bool ret = getWord(recNo, wordNo, strvalue);
  value = atoi(strvalue.c_str());
  return ret;
}

bool TextFile::getWord(int recNo, int wordNo, double& value)

  /* Extract double valued word. */
{
  String strvalue;
  bool ret = getWord(recNo, wordNo, strvalue);
  value = atof(strvalue.c_str());
  return ret;
}

String TextFile::getWord_str(int recNo, int wordNo)
{
  String strvalue;
  if (getWord(recNo, wordNo, strvalue))
    return strvalue;
  else
    return "";
}

int TextFile::getWord_int(int recNo, int wordNo)
{
  String strvalue = getWord_str(recNo, wordNo);
  return atoi(strvalue.c_str());
}

double TextFile::getWord_dbl(int recNo, int wordNo)
{
  String strvalue = getWord_str(recNo, wordNo);
  return atof(strvalue.c_str());
}

int TextFile::num_words(int recNo)
{
  if (recNo < NumRecords)
    return WordCount[recNo];
  else
    return 0;
}

bool TextFile::isActive(String line)
{
  if (line.length() <= 0 || line[0] == '#')
    return false;
  else
    return true;
}

TextFile::~TextFile(void)
{
}
