#ifndef TEST_HEADER
#define TEST_HEADER

struct State{
  int c;
  struct State *out;
  struct State *out1;
  int lastlist;
};

struct List{
  struct State **s;
  int n;
};

void setUp();

void addState(struct List *l, struct State *s);

struct List* startList(struct State *s, struct List *l);

void match(struct List *cList, int c, struct List *nList);

int matched(struct List *l);

void toString(struct List *l);

#endif
