#ifndef MINMAX_H
#define MINMAX_H

inline int maximum(const int a, const int b)
{
  return (a < b) ? b:a;
}

inline int minimum(const int a, const int b)
{
  return (a < b) ? a:b;
}

#endif
