#ifndef SSTRING_H
#define SSTRING_H

// My own special string class

#include <ctype.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

#include "boolean.h"

using namespace std;

class String {

 public:

  // String initialization
  String(void);
  String(const char c);
  String(const char* cp);
  String(const String&);

  ~String(void);

  // String assignement
  String& operator = (const String& s);
  String& assign(const String& s);

  // Extract substring
  String substring(int i1, int i2);
  
  bool resize(int newsize);

  // Return length of string without C-style termintors
  int length(void) const;

  // Return C-like string
  char* c_str(void) const;

  // Concatenation
  String& operator += (const String& s);
  friend String operator + (const String& s1, const String& s2);
  String& append(const String& s);

  // Subscripting
  char operator[] (int index) const;
  char& operator[] (int index);

  // Comparison
  friend bool operator == (const String& s1, const String& s2);
  friend bool operator != (const String& s1, const String& s2);

 private:

  int nchars;
  char *buffer;

};

// Allows one to use << operator to print strings
ostream& operator << (ostream& os, const String& s);

// Routines to write numerical values into a string
String num_to_str(int i);
String num_to_str(float i);
String num_to_str(double i);

int    str2i(String s);
double str2f(String s);

// Extract a word
int get_word(String& s, String& w, int start);

#endif
