#ifndef REGEXP_H
#define REGEXP_H

struct Nodes
{
  
};

struct State
{
  int c;
  struct State* out;
  struct State* out1;
  int lastList;
};

struct List
{
  struct State **s;
  int n;
};

_Bool is_DFA(Vector x);



#endif
