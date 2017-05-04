#include <stdio.h>
#include <stdlib.h>
#include "main.h"

struct State s13;
struct State s12;
struct State s11;
struct State s10;
struct State s9;
struct State s8;
struct State s7;
struct State s6;
struct State s5;
struct State s4;
struct State s3;
struct State s2;
struct State s1;

int listid = 0, nState  = 13, nCharClass = 256;
struct List l1, l2; //liste pré-alloué

int main(int argc, char** argv){
  //Initialise les listes
  //lance match pour chacun des caracteres de la chaine a tester
  if(argc <= 1){
    printf("Invalid Argument\n");
    exit(-1);
  }

  //init
  l1.n = 0; l2.n = 0;
  l1.s = malloc(nState * sizeof(struct State *));
  l2.s = malloc(nState * sizeof(struct State *));
  
  setUp();
  
  int i = 0, j = 0,  done = 0;
  char *s = argv[1];
  struct List *cList, *nList, *t;
  struct ListEx eList;

  eList.taille = 0;
  eList.nUnclosed = 0; 
  cList = startList(&s1, &l1);
  nList = &l2;

  ////////////
  for(; *s; s++){
    done = 0;
    while(done == 0){
      done = match(cList, *s, nList, &eList, i);
      swap(&cList, &t, &nList);
    }
    if(done == -1) break;
    i++;
  }

  if(matched(cList) == 1){
    printf("Succes\n");
    if(eList.taille > 0) printf("Expressions : \n");
    for(i = 0; i < eList.taille ; i++){
      for(j = eList.e[i].debut; j <= eList.e[i].fin; j++){
	printf("%c", argv[1][j]);
      }
      printf("\n");
    }
  }
  else printf("Failure\n");
  
  free(l1.s);
  free(l2.s);
  for(int i = 0; i < nCharClass; i++){
    free(s13.c[i]);
    free(s7.c[i]);
    free(s6.c[i]);
    free(s5.c[i]);
    free(s4.c[i]);
    free(s3.c[i]);
    free(s2.c[i]);
    free(s1.c[i]);
  }

  return 0;
}


void setUp(){
  //AUTOMATE TEST
  // aabb | abab | c

  //State 13
  for(int i = 0; i <= nCharClass; i++)
    s13.c[i] = NULL;

  s13.n = 13;
  s13.c[256] = malloc(nCharClass * sizeof(struct List*));
  s13.c[256]->n = 0;
  s13.c[256]->s = malloc(nState * sizeof(struct State*));
  s13.c[256]->s[s13.c[256]->n++] = &s13;
  
  //State 7
  for(int i = 0; i <= nCharClass; i++)
    s7.c[i] = NULL;

  s7.n = 7;
  s7.c['b'] = malloc(nCharClass * sizeof(struct List*));
  s7.c['b']->n = 0;
  s7.c['b']->s = malloc(nState * sizeof(struct State*));
  s7.c['b']->s[s7.c['b']->n++] = &s13;
  
  //State 6
  for(int i = 0; i <= nCharClass; i++)
    s6.c[i] = NULL;

  s6.n = 6;
  s6.c['a'] = malloc(nCharClass * sizeof(struct List*));
  s6.c['a']->n = 0;
  s6.c['a']->s = malloc(nState * sizeof(struct State*));
  s6.c['a']->s[s6.c['a']->n++] = &s7;
  
  //State 5
  for(int i = 0; i <= nCharClass; i++)
    s5.c[i] = NULL;

  s5.n = 5;
  s5.c['b'] = malloc(nCharClass * sizeof(struct List*));
  s5.c['b']->n = 0;
  s5.c['b']->s = malloc(nState * sizeof(struct State*));
  s5.c['b']->s[s5.c['b']->n++] = &s6;
  
  //State 4
  for(int i = 0; i <= nCharClass; i++)
    s4.c[i] = NULL;

  s4.n = 4; 
  s4.c[')'] = malloc(nCharClass * sizeof(struct List*)); 
  s4.c[')']->n = 0; 
  s4.c[')']->s = malloc(nState * sizeof(struct State*)); 
  s4.c[')']->s[s4.c[')']->n++] = &s13; 

  /* s4.n = 4; */
  /* s4.c['b'] = malloc(nCharClass * sizeof(struct List*)); */
  /* s4.c['b']->n = 0; */
  /* s4.c['b']->s = malloc(nState * sizeof(struct State*)); */
  /* s4.c['b']->s[s4.c['b']->n++] = &s13; */
  
  //State 3
  for(int i = 0; i <= nCharClass; i++)
    s1.c[i] = NULL;

  s3.n = 3;
  s3.c['b'] = malloc(nCharClass * sizeof(struct List*));
  s3.c['b']->n = 0;
  s3.c['b']->s = malloc(nState * sizeof(struct State*));
  s3.c['b']->s[s3.c['b']->n++] = &s4;

  //State 2
  for(int i = 0; i <= nCharClass; i++)
    s2.c[i] = NULL;

  s2.n = 2;
  s2.c['a'] = malloc(nCharClass * sizeof(struct List*));
  s2.c['a']->n = 0;
  s2.c['a']->s = malloc(nState * sizeof(struct State*));
  s2.c['a']->s[s2.c['a']->n++] = &s3;

  //State 1
  for(int i = 0; i <= nCharClass; i++)
    s1.c[i] = NULL;

  s1.n = 1;
  s1.c['a'] = malloc(nCharClass * sizeof(struct List*));
  s1.c['a']->n = 0;
  s1.c['a']->s = malloc(nState * sizeof(struct State*));
  s1.c['a']->s[s1.c['a']->n++] = &s5;
  /* s1.c['a']->s[s1.c['a']->n++] = &s2; */
  
  s1.c['('] = malloc(nCharClass * sizeof(struct List*));
  s1.c['(']->n = 0;
  s1.c['(']->s = malloc(nState * sizeof(struct State*));
  s1.c['(']->s[s1.c['(']->n++] = &s2;

  s1.c['c'] = malloc(nCharClass * sizeof(struct List*));
  s1.c['c']->n = 0;
  s1.c['c']->s = malloc(nState * sizeof(struct State*));
  s1.c['c']->s[s1.c['c']->n++] = &s13;
}

void manageExpr(struct ListEx *eList, int pos, int bool){
  if(! bool){
    eList->e[eList->taille].debut = pos;
    eList->unclosed[eList->nUnclosed] = eList->taille;
    eList->taille++;
    eList->nUnclosed++;
  }
  else if(bool){
    eList->e[eList->unclosed[eList->nUnclosed-1]].fin = pos-1;
    eList->nUnclosed--;
  }
}

void swap (struct List **cList, struct List **t, struct List **nList){
  *t = *cList;
  *cList = *nList;
  *nList = *t;
}

void addState(struct List *l, struct List *l2){
  // ajoute un état a la liste ssi le C de l'etat correspond a un caractere
  // si l'etat est nul ou qu'il est deja present : ne fait rien
  if(l2 == NULL) return;
  for(int i = 0; i < l2->n; i++){
    if(l2->s[i] == NULL || l2->s[i]->lastlist == listid){}
    else{
      l2->s[i]->lastlist = listid;
      l->s[l->n++] = l2->s[i];
    }
  }
}

struct List* startList(struct State *s, struct List *l){
  // initialise la liste a 0 et ajoute l'etat start a celle ci
  listid++;
  l-> n = 0;
  if(s == NULL || s->lastlist == listid);
  else{
    s->lastlist = listid++;
    l->s[l->n++] = s;
  }     
  return l;
}

int match(struct List *cList, int c, struct List *nList, struct ListEx *eList, int a){
  //ajoute les etats suivants de chacun des etats de la liste actuelle a la liste suivant
  // ssi le caractere c correspond au caractere de l'etat actuel
  int i = 0, done = -1;
  listid++;
  nList->n = 0;
  for(i = 0; i < cList->n; i++){
    if(cList->s[i]->c['('] != NULL){
      done = 0;
      manageExpr(eList, a, 0);
      addState(nList, cList->s[i]->c['(']);
    }
    if(cList->s[i]->c[')'] != NULL){
      done = 0;
      manageExpr(eList, a, 1);
      addState(nList, cList->s[i]->c[')']);
    }
    if(cList->s[i]->c[c] != NULL) {
      done = 1;
      addState(nList, cList->s[i]->c[c]);
    }
  }
  return done;
}


int matched(struct List *l){
  // Test si l'etat final est present dans la liste actuelle
  // Si c'est le cas, alors un des chemin aura atteint l'etat final et l'automate a donc reconnu la chaine de caractere
  for(int i = 0; i < l->n; i++){
    if(l->s[i]->c[256] != NULL)
      if(l->s[i]->c[256]->s[0] == &s13)
	return 1;
  }
  return 0;
}
