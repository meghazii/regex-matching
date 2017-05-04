#ifndef TEST_HEADER
#define TEST_HEADER

struct State{
  int n;
  struct List *c[257];
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

void manageExpr(struct ListEx *eList, int pos, int bool);

void swap(struct List **cList, struct List **t, struct List **nList);

void addState(struct List *l, struct List *l2);

struct List* startList(struct State *s, struct List *l);

int match(struct List *cList, int c, struct List *nList, struct ListEx *eList, int i);

int matched(struct List *l);

void toString(struct List *l);

#endif
