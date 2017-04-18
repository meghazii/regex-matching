#include <stdio.h>
#include <stdlib.h>
#include "main.h"

struct State s9;
struct State s8;
struct State s7;
struct State s6;
struct State s5;
struct State s4;
struct State s3;
struct State s2;
struct State s1;
struct State s0;

int listid = 0;
struct List l1, l2; //liste pré-alloué

int main(int argc, char** argv){
  //Initialise les listes
  //lance match pour chacun des caracteres de la chaine a tester
  
  if(argc <= 1){
    printf("Invalid Argument\n");
    exit(-1);
  }
  l1.n = 0; l2.n = 0;
  l1.s = malloc(256 * sizeof(struct State));
  l2.s = malloc(256 * sizeof(struct State));

  setUp();
  char *s = argv[1];
  printf("%s\n",s);
  struct List *cList, *nList, *t;
  struct ListEx eList;

  eList.taille = 0;
  eList.nUnclosed = 0;
  cList = startList(&s2, &l1);
  nList = &l2;
  int i = 0;
  for(; *s; s++){
    match(cList, *s, nList, &eList, i);
    t = cList;
    cList = nList;
    nList = t;
    i++;
  }
  if(matched(cList) == 1){
    printf("Succes\n");
    for(i = 0; i < eList.taille; i++){
      printf("Expression %d -> %d\n", eList.e[i].debut, eList.e[i].fin);
    }
  }
  else printf("Failure\n");
  return 0;
}


void setUp(){
  //AUTOMATE TEST
  //(ab)(ba)
  
  s9.c = 257;
  
  s8.c = ')';
  s8.out = &s9;
  
  s7.c = 'a';
  s7.out = &s9;
  
  s6.c = 'b';
  s6.out  = &s7;
  
  s5.c = '(';
  s5.out = &s6;
    
  s4.c = ')';
  s4.out = &s5;
  
  s3.c = 'b';
  s3.out = &s6;

  s2.c = 'a';
  s2.out = &s3;
  
  s1.c = '(';
  s1.out = &s2;
}

void addState(struct List *l, struct State *s){
  // ajoute un état a la liste ssi le C de l'etat correspond a un caractere
  // si l'etat est nul ou qu'il est deja present : ne fait rien
  // si l'etat correspond a un split : ajoute a la liste les etats suivants le split
  if(s == NULL || s->lastlist == listid) return;
  s->lastlist = listid;
  if(s->c == 256){
    addState(l,s->out);
    addState(l,s->out1);
    return;
  }
  l->s[l->n++] = s;
}

struct List* startList(struct State *s, struct List *l){
  // initialise la liste a 0 et ajoute l'etat start a celle ci
  listid++;
  l->n = 0;
  addState(l, s);
  return l;
}

void match(struct List *cList, int c, struct List *nList, struct ListEx *eList, int a){
  //ajoute les etats suivants de chacun des etats de la liste actuelle a la liste suivant
  // ssi le caractere c correspond au caractere de l'etat actuel
  int i = 0;
  listid++;
  nList->n = 0;
  for(i = 0; i < cList->i; i++){
    if(cList->s[i]->c == '('){
      
    }
    else if(cList->s[i]-> == ')'){
      
    }
    else if(cList->s[i]->c == c) {
      addState(nList, cList->s[i]->out);
    }
  }
}

int matched(struct List *l){
  // Test si l'etat final est present dans la liste actuelle
  // Si c'est le cas, alors un des chemin aura atteint l'etat final et l'automate a donc reconnu la chaine de caractere
  int i = 0;
  for(i = 0; i < l->n; i++){
    if(l->s[i]->c == 257){
      return 1;
    }
    return 0;
  }
  return 0;
}
