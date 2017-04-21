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

struct Expr{
  int debut;
  int fin;
};

struct ListEx{
  struct Expr e[256];
  int taille;
  int unclosed[256];
  int nUnclosed;
};

void setUp();

void manageExpr(struct List *cList, int i, struct ListEx *eList, int a);

void swap(struct List **cList, struct List **t, struct List **nList);

void addState(struct List *l, struct State *s);

struct List* startList(struct State *s, struct List *l);

void match(struct List *cList, int c, struct List *nList);

int matched(struct List *l);

void toString(struct List *l);

#endif
