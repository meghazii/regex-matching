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

  cList = startList(&s1, &l1);
  nList = &l2;

  int test = 1, i = 0, compteur = 0;

  for(; *s; s++){
    do{
      test = 1;
      for(compteur = 0; compteur < cList->n; compteur++){

	if(cList->s[compteur]->c == '(' || cList->s[compteur]->c == ')'){
	  test = 0;
	  manageExpr(cList, compteur, &eList, i);
	  listid++;
	  nList->n = 0;
	  addState(nList, cList->s[compteur]->out);
	  swap(&cList, &t, &nList);
	}
      }
    }while(test == 0);
    match(cList, *s, nList);
    swap(&cList, &t, &nList);
    i++;
  }
  do{
    test = 1;
    for(compteur = 0; compteur < cList->n; compteur++){
      if(cList->s[compteur]-> c == '(' || cList->s[compteur]-> c == ')'){
	test = 0;
	manageExpr(cList, compteur, &eList, i);
	listid++;
	nList->n = 0;
	addState(nList, cList->s[compteur]->out);
	swap(&cList, &t, &nList);
      }
    }
  }while(test == 0);

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
  //(ab)(ba)

  s12.c = 257;
  
  s11.c = ')';
  s11.out = &s12;
  
  s10.c = 'b';
  s10.out = &s11;
  
  s9.c = 'a';
  s9.out = &s10;

  s8.c = 'b';
  s8.out = &s9;
  
  s7.c = 'a';
  s7.out = &s8;
  
  s6.c = 'b';
  s6.out = &s7;
  
  s5.c = '(';
  s5.out = &s6;
    
  s4.c = ')';
  s4.out = &s5;
  
  s3.c = 'b';
  s3.out = &s4;

  s2.c = 'a';
  s2.out = &s3;
  
  s1.c = '(';
  s1.out = &s2;
}

void manageExpr(struct List *cList, int i, struct ListEx *eList, int a){
  if(cList->s[i]->c == '('){
    eList->e[eList->taille].debut = a;
    eList->unclosed[eList->nUnclosed] = eList->taille;
    eList->taille++;
    eList->nUnclosed++;
  }
  else if(cList->s[i]->c == ')'){
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

void match(struct List *cList, int c, struct List *nList){
  //ajoute les etats suivants de chacun des etats de la liste actuelle a la liste suivant
  // ssi le caractere c correspond au caractere de l'etat actuel
  int i = 0;
  listid++;
  nList->n = 0;
  for(i = 0; i < cList->n; i++){
    if(cList->s[i]->c == c) {
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
  }
  return 0;
}
