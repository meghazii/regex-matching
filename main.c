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

int listid = 0, N  = 13;
struct List l1, l2; //liste pré-alloué

int main(int argc, char** argv){
  //Initialise les listes
  //lance match pour chacun des caracteres de la chaine a tester
  if(argc <= 1){
    printf("Invalid Argument\n");
    exit(-1);
  }
  l1.n = 0; l2.n = 0;
  l1.s = malloc(N * sizeof(struct State *));
  l2.s = malloc(N * sizeof(struct State *));
  
  setUp();
  char *s = argv[1];
  printf("%s\n",s);
  struct List *cList, *nList, *t;
  struct ListEx eList;
  struct State etat;
  eList.taille = 0;
  eList.nUnclosed = 0;

  cList = startList(&s1, &l1);
  nList = &l2;

  int i = 0, compteur = 0,  done = 0;
  int x = 0;
  for(; *s; s++){
    printf("START --> %c\n", *s);
    done = 0;
    while(done == 0){
      done = match(cList, *s, nList, &eList,i);
      swap(&cList, &t, &nList);
    }
    if(done == -1) break;
    i++;
  }
  
  if(matched(cList) == 1){
    printf("Succes\n");
    printf("Expressions : \n");
    for(i = 0; i < eList.taille ; i++){
      for(compteur = eList.e[i].debut; compteur <= eList.e[i].fin; compteur++){
	printf("%c", argv[1][compteur]);
      }
      printf("\n");
    }
    
  }
  else printf("Failure\n");
  return 0;
}


void setUp(){
  //AUTOMATE TEST
  //(ab)*c

  //s13.c = 257;
  
  /* s12.c = ')';
     s12.out = &s1;
  
     s11.c = 25;
     s11.out = &s9;
     s11.out1 = &s12;
  
     s10.c = ')';
     s10.out = &s1;
  
     s9.c = 'b';
     s9.out = &s11;

     s8.c = ')';
     s8.out = &s1;
  
     s7.c = 256;
     s7.out = &s8;
     s7.out1 = &s4;
  
     for(int i = 0; i < 257; i++)
     s6.c[i] = NULL;
  */
  for(int i = 0; i < 257; i++)
    s5.c[i] = NULL;

  s5.n = 5;
  s5.c[256] = &s5;
  
  /*  for(int i = 0; i < 257; i++)
    s4.c[i] = NULL;

  s4.n = 4;
  s4.c[')'] = &s1;
  
  for(int i = 0; i < 257; i++)
    s3.c[i] = NULL;

  s3.n = 3;
  s3.c['b'] = &s4;*/
  
  for(int i = 0; i < 257; i++)
    s2.c[i] = NULL;

  s2.n = 2;
  s2.c['a'] = &s2;
  s2.c['b'] = &s2;
  s2.c[')'] = &s1;
  
  for(int i = 0; i < 257; i++)
    s1.c[i] = NULL;

  s1.n = 1;
  s1.c['('] = &s2;
  s1.c['c'] = &s5;
}

void manageExpr(struct List *cList, struct ListEx *eList, int a, int b){
  if(! b){
    eList->e[eList->taille].debut = a;
    eList->unclosed[eList->nUnclosed] = eList->taille;
    eList->taille++;
    eList->nUnclosed++;
  }
  else if(b){
    eList->e[eList->unclosed[eList->nUnclosed-1]].fin = a-1;
    eList->nUnclosed--;
  }
}

void swap (struct List **cList, struct List **t, struct List **nList){
  *t = *cList;
  *cList = *nList;
  *nList = *t;
}

void addState(struct List *l, struct State *s){
  // ajoute un état a la liste ssi le C de l'etat correspond a un caractere
  // si l'etat est nul ou qu'il est deja present : ne fait rien
  // si l'etat correspond a un split : ajoute a la liste les etats suivants le split
  if(s == NULL || s->lastlist == listid) return;
  s->lastlist = listid;
  l->s[l->n++] = s;
}

struct List* startList(struct State *s, struct List *l){
  // initialise la liste a 0 et ajoute l'etat start a celle ci
  listid++;
  l->n = 0;
  addState(l, s);
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
      manageExpr(cList, eList, a, 0);
      addState(nList, cList->s[i]->c['(']);
    }
    if(cList->s[i]->c[')'] != NULL){
      done = 0;
      manageExpr(cList, eList, a, 1);
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
  int i = 0;
  for(i = 0; i < l->n; i++){
    if(l->s[i]->c[256] == &s5){
      return 1;
    }
  }
  return 0;
}
