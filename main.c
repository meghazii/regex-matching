#include <stdio.h>
#include <stdlib.h>
#include "main.h"

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

int listid = 0;
struct List l1, l2, t; //liste pré-alloué

int main(int argc, char** argv){
  //Initialise les listes
  //lance match pour chacun des caracteres de la chaine a tester
  
  if(argc <= 1){
    printf("Invalid Argument\n");
    exit(-1);
  }
  l1.n = 0; l2.n = 0; t.n = 0;
  l1.s = malloc(256 * sizeof(struct State));
  l2.s = malloc(256 * sizeof(struct State));
  t.s = malloc(256*sizeof(struct State));
  
  setUp();
  char *s = argv[1];
  printf("%s\n",s);
  struct List *cList, *nList; 
  struct ListEx eList;
  eList.taille = 0;
  eList.nUnclosed = 0;

  cList = startList(&s1, &l1);
  nList = &l2;
  int i = 0;
  for(; *s; s++){
    match(cList, *s, nList, &t, &eList, i);
      //t = cList;
    cList = nList;
    nList = &t;
      

    i++;
  }
  if(cList->s[0]->c == ')'){
    match(cList, *s, nList, &t, &eList, i);
    if(cList->s[0]->c == ')'){
      //t = cList;
      cList = nList;
      nList = &t;
    }
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

  s12.c = 257;
  
  s11.c = ')';
  s11.out = &s12;
  
  s10.c = ')';
  s10.out = &s11;
  
  s9.c = 'a';
  s9.out = &s10;

  s8.c = ')';
  s8.out = &s9;
  
  s7.c = 'b';
  s7.out = &s8;
  
  s6.c = '(';
  s6.out = &s7;
  
  s5.c = '(';
  s5.out = &s6;
    
  s4.c = ')';
  s4.out = &s5;
  
  s3.c = 'a';
  s3.out = &s4;

  s2.c = '(';
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
  //printf("Next Char : %c\n", s->c);
}

struct List* startList(struct State *s, struct List *l){
  // initialise la liste a 0 et ajoute l'etat start a celle ci
  listid++;
  l->n = 0;
  addState(l, s);
  return l;
}

int match(struct List *cList, int c, struct List *nList, struct List *t, struct ListEx *eList, int a){
//ajoute les etats suivants de chacun des etats de la liste actuelle a la liste suivant
// ssi le caractere c correspond au caractere de l'etat actuel
  int i = 0, done = 0;
  listid++;
  printf("cList : %d, nList : %d\n", cList->n, nList->n);
  if(nList->n > 0)printf("  Char nList -> %c\n", nList->s[0]->c);
  printf("TEST : %c -> %c\n", cList->s[0]->c, c);
  nList->n = 0;
  for(i = 0; i < cList->n; i++){
    if(cList->s[i]->c == '('){
      eList->e[eList->taille].debut = a;
      eList->unclosed[eList->nUnclosed] = eList->taille;
      eList->taille++;
      eList->nUnclosed++;
      
      addState(nList, cList->s[i]->out);
      //t = cList;
      cList = nList;
      nList = t;
      done = 1;
      match(cList, c, nList,t, eList, a);

    }
    else if(cList->s[i]->c == ')'){
      eList->e[eList->unclosed[eList->nUnclosed-1]].fin = a-1;
      eList->nUnclosed--;

      addState(nList, cList->s[i]->out);
      //t = cList;
      cList = nList;
      nList = t;
      match(cList, c, nList,t, eList, a);
    }
    else if(cList->s[i]->c == c) {
      addState(nList, cList->s[i]->out);
    }
  }
  return done;
}


int matched(struct List *l){
  // Test si l'etat final est present dans la liste actuelle
  // Si c'est le cas, alors un des chemin aura atteint l'etat final et l'automate a donc reconnu la chaine de caractere
  int i = 0;
  for(i = 0; i < l->n; i++){
    if(l->s[i]->c == 257){
      return 1;
    }
  }
  return 0;
}
