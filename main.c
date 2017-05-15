#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int cc = 257; //nombre de charclass
int nNodes = 4; //nombre de noeud/état dans l'automate
Lisp_Object array;

int main(){
  
  //récupere tableau lisp de taille : cc * nNodes
  //soit x % (cc * nNodes) + cTable = une classe de caractere

  int currentState;
  char** s = "abba";
 
  for(; *s; s++)
    {
      currentState = f(*s, currentState);
      if(currentState == 0 || currentState == -1) break;
    }

  if(currentState == 0) printf("Succes\n");
  else printf("Fail\n");
  return 0;
}

  
int DFA(char c, int currentState)
{
  if(AREF(array, CHAR_TABLE(c)) != Qnil)
    {
      if(INTEGERP(AREF(array, CHAR_TABLE(c))))
	{
	  return(AREF(array, CHAR_TABLE(c)));
	}
      else
	{
	  return -1;
	}
    }
}

int
DFA_Mark(Lisp_Object cMap, int ncc, Lisp_Object c, int cState, Lisp_Object array)
{
  
  Lisp_Object tmp = AREF (array, cState*ncc + cc1);
  if (INTEGERP (tmp))
    {
      Lisp_Object cc = Faref (cMap, c);
      if (! INTEGERP(cc))
	{
	  error ("plop 2");
	}
      int cc1 = XINT(cc);
      if (cc1 >= ncc)
	{
	  error ("plop 3");
	}
      return XINT(tmp);
    }
  else if (CONSP(tmp))
    {
      save (XCAR (XCDR (tmp)));
      DFA_Mark (XCAR (XCDR (XCDR (tmp))));
    }
  else
    {
      error ("plop");
    }
}
