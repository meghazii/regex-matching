#ifndef REGEXP_H
#define REGEXP_H

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

void addState(struct List *l, struct State *s);

struct List* startList(struct State *s, struct List *l);

void match(struct List *cList, int c, struct List *nList);

int is_matched(struct List *l);

#endif
