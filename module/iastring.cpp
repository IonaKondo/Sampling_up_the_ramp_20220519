#include "iastring.h"

int string2words(String& sentence, IAString& words)

  /* Decompose a "sentence" into a list of words, where a "word" is
     defined to be separated by spaces. */
{
  int numChar = sentence.length();

  int wordNo = 0;
  int charNo = 0;

  while (charNo < numChar) {

    // Move to the next non-space
    while (isspace(sentence[charNo]) && charNo < numChar) ++charNo;
    int idx1 = charNo;

    // Move to the next space
    while (!isspace(sentence[charNo]) && charNo < numChar) ++charNo;
    int idx2 = charNo;

    // Found a word
    String word = sentence.substring(idx1, idx2 - 1);

    if (word.length() > 0) {
      words[wordNo] = word;
      ++wordNo;
    }
  }

  return wordNo;
}

