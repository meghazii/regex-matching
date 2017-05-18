#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main(){

  return 0;
}

int
NFA_matching (Lisp_Object cMap, int ncc, Lisp_Object c, int cState, Lisp_Object array)
{
  DEFSYM ("if", Qif); DEFSYM ("Or", Qor); DEFSYM ("mark", Qmark);
  Lis_Object cc = Faref (cMap, c);
  if (! INTEGERP(cc))
    {
      error (" plopv2");
    }
  int cc1 = XINT(cc);
  Lisp_Object tmp = AREF (array, cState*ncc + cc1);

  if (cc1 >= ncc)
    {
      error ("plopv2 2");
    }
  if (INTEGERP (tmp))
    {
    }
  else if (CONSP (tmp))
    {
      if (EQ (XCAR (tmp), Qif))
	{
	}
      else if (EQ (XCAR (tmp), Qor))
	{
	}
      else if (EQ (XCAR (tmp), Qmark))
	{
	}
    }
  else
    {
    }
}

int
DFA_Mark (Lisp_Object cMap, int ncc, Lisp_Object c, int cState, Lisp_Object array)
{
  DEFSYM("mark", Qmark);
  Lisp_Object cc = Faref (cMap, c);
  if (! INTEGERP(cc))
    {
      error ("plop 2");
    }
  int cc1 = XINT(cc);
  Lisp_Object tmp = AREF (array, cState*ncc + cc1);
  
  if (cc1 >= ncc)
    {
      error ("plop 3");
    }
  if (INTEGERP (tmp))
    {
      return XINT (tmp);
    }
  else if (CONSP (tmp))
    {
      if (EQ (XCAR (tmp), Qmark))
	{
	  save (XCAR (XCDR (tmp)));
	  DFA_Mark (cMap, ncc, c, cState, array);
	}
    }
  else
    {
      error ("plop");
    }
}

int
DFA_matching (Lisp_Object cMap, int ncc, Lisp_Object c, int cState, Lisp_Object array)
{
  Lisp_Object cc = Faref (cMap, c);
  if (! INTEGERP(cc))
    {
      error ("plop 2");
    }
  int cc1 = XINT(cc);
  Lisp_Object tmp = AREF (array, cState*ncc + cc1);
  
  if (cc1 >= ncc)
    {
      error ("plop 3");
    }
  if (INTEGERP (tmp))
    {
      return XINT(tmp);
    }
  else
    {
      error ("plop");
    }
}

Lisp_Object
match(Lisp_Object array, Lisp_Object cMap, Lisp_Object string, unsigned int ncc, unsigned int nState)
{
  int cState = 0;
  eassert (STRINGP (string));
  char *s = malloc(4 * sizeof(char));
  *s = XSTRING (string);
  for (; *s; s++)
    {
      cState = DFA_matching (cMap, ncc, string, cState, array);
      if (cState == 0 || cState == -1) break;
    }
  if (cState == 0) return 1;
  else return 0;
}

DEFUN ("DFA_matching", FDFA_matching, SDFA_matching, 5, 5, 0, doc : )
  (Lisp_Object array, Lisp_Object cMap, Lisp_Object string, unsigned int ncc, unsigned int nState)
{
  return match(array, cMap, string, ncc, nState);
}


int
test ()
{
  /* l1.n = 0; l2.n = 0; */
  /* l1.s = malloc (256 * sizeof (struct State)); */
  /* l2.s = malloc (256 * sizeof (struct State)); */
  /* char *s = argv[1]; */
  /* printf ("%s\n",s); */
  struct List *cList, *nList, *t;
  
  cList = startList (&s1, &l1);
  nList = &l2;
  int i = 0;
  for (; *s; s++)
    {
      match (cList, *s, nList);
      t = cList;
      cList = nList;
      nList = t;
      i++;
    }
  if (matched (cList) == 1)
    {
      printf ("Succes\n");
    }
  else printf ("Failure\n");
  return 0;
}

void
addState (struct List *l, struct State *s)
{
  if (s == NULL || s->lastlist == listid) return;
  s->lastlist = listid;
  if (s->c == 256)
    {
      addState (l,s->out);
      addState (l,s->out1);
      return;
    }
  l->s[l->n++] = s;
}

struct List*
startList (struct State *s, struct List *l)
{
  listid++;
  l->n = 0;
  addState (l, s);
  return l;
}

void
match (struct List *cList, int c, struct List *nList)
{
  int i = 0;
  listid++;
  nList->n = 0;
  for (i = 0; i < cList->n; i++)
    {
      if (cList->s[i]->c == c)
	{
	  addState (nList, cList->s[i]->out);
	}
    }
}

int
matched (struct List *l)
{
  int i = 0;
  for (i = 0; i < l->n; i++)
    {
      if (l->s[i]->c == 257)
	{
	  return 1;
	}
      return 0;
    }
  return 0;
}
