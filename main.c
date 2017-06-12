
struct State
{
  int id;
  int *lpos;
};

struct List
{
  struct State *s;
  int n;
};

static void
addState (struct List *l, int s, int* lmark, int nMark)
{
  for (int i = 0; i < l->n; i++)
    if (l->s[i].id == s) return;
  
  l->s[l->n++].id = s;
  l->s->lpos = malloc (nMark*sizeof (int));
  memcpy(l->s->lpos, lmark, nMark*sizeof(int));
}

static struct List*
startList (int a, struct List *l, int* lmark, int nMark)
{
  l->n = 0;
  addState (l, a, lmark, nMark);
  return l;
}

static bool
matched (struct List *l)
{
  for (int i = 0; i < l->n; i++)
    {
      if (l->s[i].id == -2)
	{
	  return true;
	}
    }
  return false;
}

static bool
specialChar (int test, int pos)
{
  Lisp_Object lchar;
  if (test == 0)
    {
      lchar = Fchar_after (make_number (pos-1));
      if (! INTEGERP (lchar))
	error ("Not Integer");
      if (XINT (lchar) == '\n')
	return true;
      else return false; 
    }
  else if (test == 1)
    {
      lchar = Fchar_after (make_number (pos+1));
      if (! INTEGERP (lchar))
	error ("Not Integer");
      if (XINT (lchar) == '\n')
	return true;
      else return false;
    }
  return false;
}

static void
  NFA_matching (Lisp_Object cMap, int ncc, Lisp_Object c, int cState, struct List* nList, Lisp_Object array, int *lmark, int pos, int nMark)
{
  Lisp_Object cc = Faref (cMap, c);
  if (! INTEGERP (cc))
    error ("Error : Unknown char class");
  
  int cc1 = XINT (cc);
  if (cc1 > ncc)
    error ("Error : Impossible Value");

  if (cState < 0)
    return;

  if (cState * ncc + cc1 >= ASIZE (array))
    error ("Error : Out of Bound");

  
  Lisp_Object tmp = AREF (array, cState * ncc + cc1);

  if (CONSP (tmp))
    {
      if (EQ (XCAR (tmp), Qif))
	{
	  bool test = specialChar (XINT (XCAR (XCDR (tmp))), pos);
	  tmp = XCDR (XCDR (tmp));
	  if (test)
	    {
	      if (EQ (XCAR (tmp), Qnil))
		error ("Error : Unvalid state");
	      addState (nList, XINT (XCAR (tmp)), lmark, nMark);
	    }
	  else
	    {
	      if (EQ (XCAR (XCDR (tmp)), Qnil))
		error ("Error : Unvalid state");
	      addState (nList, XINT (XCAR (XCDR (tmp))), lmark, nMark);
	    }
	}
      else if (EQ (XCAR (tmp), Qmark))
	{
	  int buf = XINT (XCAR (XCDR (tmp)));
	  *(lmark+buf) = pos;
	  addState (nList, XINT (XCAR (XCDR (XCDR (tmp)))), lmark, nMark);
	}
	  
      else if (EQ (XCAR (tmp), Qor))
	{
	  tmp = XCDR (tmp);
	  while (! NILP (tmp))
	    {
	      addState (nList, XINT (XCAR (tmp)), lmark, nMark);
	      tmp = XCDR (tmp);
	    }
	}
    }
  else if (INTEGERP (tmp))
    {
      addState (nList, XINT (tmp), lmark, nMark);
    }
  else
    error ("Error : Unknown type");
}

static int
DFA_matching (Lisp_Object cMap, int ncc, Lisp_Object c, int cState, Lisp_Object array)
{
  Lisp_Object cc = Faref (cMap, c);
  if (! INTEGERP (cc))
    error ("Error : Unknow char class");
  
  int cc1 = XINT (cc);
  if (cc1 > ncc)
    error ("Error : Impossible Value");
  
  if (cState * ncc + cc1 >= ASIZE (array))
    error ("Error : Out of Bound");
  
  Lisp_Object tmp = AREF (array, cState * ncc + cc1);
  
  if (INTEGERP (tmp))
    return XINT (tmp);
  else
    error ("Error : Unknown type");
}

static Lisp_Object
match (Lisp_Object array, Lisp_Object cMap, unsigned int ncc, int nState, bool b, int nMark)
{
  int cState = 0;  
  EMACS_INT pos = BEGV;
  EMACS_INT lmatch = 0;
  Lisp_Object lchar;

  if(! b)
    {
      while (pos != ZV && cState != -2)
	{
	  lchar = Fchar_after (make_number (pos));
	  if (! INTEGERP (lchar))
	    return Qnil;
	  pos++;
	  cState = DFA_matching (cMap, ncc, lchar, cState, array);
	  if (cState == -1)
	    cState = 0;
	}

      if (cState == -2)
	return make_number (pos);
      else return Qnil;
    }
  else
    { 
      struct List *cList, *nList, *t;
      struct List l1, l2;
      int *lmark = malloc (nMark * sizeof (int));
      l1.n = 0; l2.n = 0;
      l1.s = malloc (nState * sizeof (struct State));
      l2.s = malloc (nState * sizeof (struct State));
      cList = startList (cState, &l1, lmark, nMark);
      nList = &l2;

      while (pos != ZV)
	{
	  lchar = Fchar_after (make_number (pos));
	  pos++;
	  for (int i = 0; i < cList->n; i++)
	    NFA_matching (cMap, ncc, lchar, cList->s[i].id, nList, array, lmark, pos, nMark);
	  t = cList;
	  cList = nList;
	  nList = t;
	  nList->n = 0;

	  if (matched (cList))
	    lmatch = pos;
	  if (cList->n == 0)
	    break;
	}

      for (int i = 0; i < cList->n; i++)
	{
	  if (cList->s[i].id == -2)
	    {
	      for (int j = 0; j < nMark; j++)
		message ("Mark %d : %d", j, *(cList->s[i].lpos+j));
	      break;
	    }
	}
    }
  if (lmatch > 0)
    return make_number (lmatch-2);
  else
    return Qnil;
}

DEFUN ("DFA-match", Fdfa_match, Sdfa_match, 4, 4, 0,
       doc: /**/)
  (Lisp_Object array, Lisp_Object cMap, Lisp_Object ncc, Lisp_Object nState)
{
  return match (array, cMap, XINT (ncc), XINT (nState), false, 0);
}

DEFUN ("NFA-match", Fnfa_match, Snfa_match, 5, 5, 0,
       doc: /**/)
  (Lisp_Object array, Lisp_Object cMap, Lisp_Object ncc, Lisp_Object nState, Lisp_Object nMark)
{
  return match (array, cMap, XINT (ncc), XINT (nState), true, XINT (nMark));
}
