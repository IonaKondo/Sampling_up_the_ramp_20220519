/******************************************************************************
*                                                                             *
*  Working string class. The functions are minimial for now, but I'll add     *
*  more as I need them                                                        *
*                                                                             *
*  Ian Bond, 22/3/2001                                                        *
*                                                                             *
******************************************************************************/

#include "sstring.h"

String::String(void)
{
  buffer = 0;
  nchars = 0;
}

String::String(const char c)
{
  buffer = new char[2];
  buffer[0] = c;
  buffer[1] = '\0';
  nchars = 2;
}

String::String(const char* cp)
{
  if (cp != 0) {
    int len = strlen(cp);
    buffer = new char[len + 1];
    if (len > 0) 
      strcpy(buffer, cp);
    else
      buffer[0] = '\0';
    nchars = len;
  }
  else {
    buffer = 0;
    nchars = 0;
  }
}

String::String(const String& s)
{
  nchars = s.nchars;

  if (nchars > 0) {
    buffer = new char[nchars + 1];
    strcpy(buffer, s.buffer);
  }
  else
    buffer = 0;
}

String::~String(void)
{
  if (buffer) delete[] buffer;
}

String& String::operator = (const String& s)
{
  return assign(s);
}

String& String::assign(const String& s)
{
  if (buffer && nchars > 0) delete[] buffer;
  
  nchars = s.nchars;

  if (s.buffer != 0) {
    buffer = new char[nchars + 1];
    strcpy(buffer, s.buffer);
  }
  else
    buffer = 0;

  return *this;
}

String String::substring(int i1, int i2)
{
  int len = i2 - i1 + 1;
  char *temp = new char[len+1];
  int i;
  for (i = i1; i <= i2; ++i) temp[i-i1] = buffer[i];
  temp[len] = '\0';
  String substr(temp);
  return substr;
}

bool String::resize(int newsize)
{
  if (buffer && nchars > 0) delete[] buffer;

  nchars = newsize;
  if ((buffer = new char[nchars + 1]))
    return true;
  else
    return false;
}

/*---------------------------------------------------------------------------*/

int String::length(void) const
{
  return nchars;
}

char* String::c_str(void) const
{
  return buffer;
}

/*---------------------------------------------------------------------------*/

String& String::operator += (const String& s)
{
  return append(s);
}

String operator + (const String& s1, const String& s2)
{
  String temp = s1;
  temp += s2;
  return temp;
}

String& String::append(const String& s)

  /* Simple append function. Just append the whole input string onto
     the current string. */
{
  if (buffer) {
    char *temp = new char[nchars + 1];
    strcpy(temp, buffer);
    delete[] buffer;
    
    nchars += s.nchars;
    buffer = new char[nchars + 1];
    
    strcpy(buffer, temp);
    strcat(buffer, s.buffer);
    
    delete[] temp;
  }
  else
    assign(s);

  return *this;
}

// Subscripting
char String::operator[] (int index) const
{
  return buffer[index];
}

char& String::operator[] (int index)
{
  return buffer[index];
}

bool operator == (const String& s1, const String& s2)
{
  return ( strcmp(s1.buffer, s2.buffer) == 0 ? true : false);
}

bool operator != (const String& s1, const String& s2)
{
  return (s1 == s2 ? false : true);
}

/*---------------------------------------------------------------------------*/

// Allows one to use << operator to print strings
ostream& operator << (ostream& os, const String& s)
{
  os << s.c_str();
  return os;
}

String num_to_str(int i)

  /* Converts integer to a string. */
{
  char c_str[30];
  sprintf(c_str, "%d", i);
  String str = c_str;
  return str;
}

String num_to_str(float x)

  /* Converts float to a string. */
{
  char c_str[30];
  sprintf(c_str, "%f", x);
  String str = c_str;
  return str;
}

String num_to_str(double x)

  /* Converts double to a string. */
{
  char c_str[30];
  sprintf(c_str, "%f", x);
  String str = c_str;
  return str;
}

int str2i(String s){
  return atoi(s.c_str());
}

double str2f(String s){
  return atof(s.c_str());
}

int get_word(String& s, String& w, int start)

  /* Extract the next word from the starting character. */
{
  int nchar = start;

  // Move to the next non-space
  while (isspace(s[nchar]) && nchar < s.length()) ++nchar;
  int idx1 = nchar;

  // Move to the next space
  while (!isspace(s[nchar]) && nchar < s.length()) ++nchar;
  int idx2 = nchar;
  
  w = s.substring(idx1, idx2-1);

  if (idx2 >= s.length()) idx2 = -1;

  return idx2;
}

