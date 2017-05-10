#ifndef REGEXP_HEADER
#define REGEXP_HEADER

struct State{
  int n;
  struct List *c[257];
  int lastlist;
};

struct List{
  struct State **s;
  int n;
};

#endif
