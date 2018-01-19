#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "Chaussette.h"

static char *getRank(char *name, char *words, int *i)
{
  char **tmp;
  char *str;
  int parsing;
  int j;

  j = *i;
  j += 2;
  if ((tmp = malloc(2 * sizeof(char *))) == NULL)
    my_perror(M_FAIL);
  if ((tmp[0] = malloc(1)) == NULL)
    my_perror(M_FAIL);
  tmp[1] = NULL;
  tmp[0][0] = 0;
  str = NULL;
  name = my_realloc(name, '[');
  while (words[j] != ']')
    {
      tmp[0] = my_realloc(tmp[0], words[j]);
      j++;
    }
  *i = j;
  parsing = parseer.words;
  parseer.words = -1;
  str = my_getstr(getVal(tmp));
  name = my_strcat(name, str, FAILURE);
  name = my_realloc(name, ']');
  parseer.words = parsing;
  if (str && str[0] != '0')
    free(str);
  free_tab(tmp);
  return (name);
}

char *getOnlyName(char *words)
{
  char *name;
  int i;
  int inc;

  if ((name = malloc(sizeof(char *) * (my_strlen(words) + 1))) == NULL)
    my_perror(M_FAIL);
  name[0] = 0;
  i = 1;
  inc = 0;
  while (words[i])
    {
      if (words[i] == '[')
      	{
    name = getRank(name, words, &i + 1);
	  inc = my_strlen(name);
	  name = my_realloc(name, 0);
	  while (words[i] != ']')
	    i++;
	}
      else
	{
	  name = my_realloc(name, words[i]);
	  //name[inc + 1] = 0;
	}
      i++;
      inc++;
    }
  if (name == NULL || name[0] == 0)
  {
    my_putstr(words);
    perrorPars(NULL, "The poor variable need a name");
  }
  return (name);
}

static t_var *lookVarForAdrFromName(char *name, char location)
{
  t_var *adr;
  int comp;

  adr = 0;
  comp = 0;
  if ((adr = malloc(sizeof(t_var))) == NULL)
    perrorPars(NULL, M_FAIL);
  adr[0].name = NULL;
  while (comp < NB_VAR)
  {
    if (location == varSyn[comp].str[0])
    {
      parseer.check = SUCCESS;
      adr = varSyn[comp].struc(name);
      return (adr);
    }
    comp++;
  }
  parseer.check = FAILURE;
  return (adr);
}

static int *lookVarForAdr(char **words)
{
	char *hash;
	int *adr;
	int comp;

	testNULL(words);
	adr = 0;
	comp = 0;
	hash = getOnlyName(words[parseer.words]);
	while (comp < NB_VAR)
	{
		if (words[parseer.words][0] == varSyn[comp].str[0])
		{
			parseer.check = SUCCESS;
			adr = varSyn[comp].var(hash);
			return (adr);
		}
		comp++;
	}
	free(hash);
	parseer.check = FAILURE;
	return (adr);
}

static int compArg(char *op, t_ptr *ptr)
{
	int i;

	i = 0;
	while (i != NB_OP)
	{
		if (!my_strcmp(op, ptr[i].str))
			return(i);
		i++;
	}
	return (FAILURE);
}

static int execOp(char **words)
{
  char *op;
  int res;
  int comp;
  int i;
  int j;

  parseer.check = FAILURE;
  res = 0;
  op = NULL;
  op = my_strcpy(op, words[parseer.words], FAILURE);
  i = 0;
  j = 0;
  if (!my_strcmp(op, "!"))
    {
      free(op);
      parseer.check = SUCCESS;
      return (getFunc(NULL, words));
    }
  if (!my_strcmp(op, "!!"))
    {
      i = getVal(words);
      free(op);
      parseer.check = SUCCESS;
      return (i);
    }
  comp = compArg(op, ptr);
  if (comp != FAILURE)
    {
      i = getVal(words);
      j = getVal(words);
      res = ptr[comp].op(i, j);
      parseer.check = SUCCESS;
    }
  free(op);
  return (res);
}

static int lookVar(char **words)
{
  char *hash;
  int *adr;
  int comp;

  testNULL(words);
  comp = 0;
  if (isJustInt(words[parseer.words])){
      parseer.check = SUCCESS;
      return (my_getnbr(words[parseer.words], FAILURE));
  }
  hash = getOnlyName(words[parseer.words]);
  while (comp < NB_VAR)
    {
      if (words[parseer.words][0] == varSyn[comp].str[0])
		{
      parseer.check = SUCCESS;
		  adr = varSyn[comp].var(hash);
	  	  return (*adr);
		}
      comp++;
    }
  free(hash);
  parseer.check = FAILURE;
  return (FAILURE);
}

int *getAdr(char **words)
{
  int *adr;

  parseer.words++;
  testNULL(words);
  if (words[parseer.words][0] == '(' || words[parseer.words][0] == ')')
    parseer.words++;
  adr = lookVarForAdr(words);
  if (parseer.check == FAILURE)
    perrorPars(words, SYN_ERR);
  parseer.check = FAILURE;
  return (adr);
}

int getVal(char **words)
{
  int value;
  t_type type = _int;
  t_var *var;

  parseer.words++;
  value = 0;
  parseer.string = 0;
  testNULL(words);
  if (!my_strcmp(words[parseer.words], "(")
      || !my_strcmp(words[parseer.words], ")"))
    parseer.words++;
  value = execOp(words);
  if (parseer.check == FAILURE)
    {
      value = lookVar(words);
      type = getType(words);
      if (parseer.check == FAILURE)
        perrorPars(words, SYN_ERR);  
    }
  parseer.check = FAILURE;
  if (type == _char)
    return ((char)value);
  else if (type == _string)
  {
    if (mem.var_stack)
      free(mem.var_stack);
    var = getVarFromPart(words);
    if ((mem.var_stack = malloc(sizeof(t_var) * (memLen(var) + 1))) == NULL)
      perrorPars(words, M_FAIL);
    if (memCopy(mem.var_stack, var) == FAILURE)
      perrorPars(words, "Copy failed");
    parseer.string = 1;
    freeVar(var);
    return ((int)value);
  }
  else
    return ((int)value);
}

t_type getType(char **words)
{
  int comp;
  char *hash;
  t_type type;

  comp = 0;
  type = _null;
  if (isJustInt(words[parseer.words])){
    return (_int);
  }
  hash = getOnlyName(words[parseer.words]);
  while (comp != NB_TYPE)
  {
    if (words[parseer.words][0] == varSyn[comp].str[0])
    {
      parseer.check = SUCCESS;
      type = varSyn[comp].type(hash);
      return (type);
    }
    comp++;
  }
  free(hash);
  return(_int);
}

static int *switchString(char *var)
{
  char *name;
  char *append;
  char *find;
  int   i;
  int   inc;
  t_var *adr;

  i = 0;
  inc = 0;
  name = my_hashstr(var, 1, my_strlen(var), FAILURE);
  adr = lookVarForAdrFromName(name, var[0]);
  adr->type = _string;
  while (mem.var_stack[i].name)
  {
    while (mem.var_stack[i].name[inc] && mem.var_stack[i].name[inc] != '[' && mem.var_stack[i].name[inc] != '.')
      inc++;
    append = my_hashstr(mem.var_stack[i].name, inc, my_strlen(mem.var_stack[i].name), FAILURE);
    if (my_strlen(append))
    {
      find = my_strcpy(find, name, FAILURE);
      find = my_strcat(find, append, FAILURE);
      adr = lookVarForAdrFromName(find, var[0]);
      if (parseer.check == FAILURE)
        perrorPars(NULL, SYN_ERR);
      if (mem.var_stack[i].type == _int)
        *(int *)adr->value = *(int *)mem.var_stack[i].value;
      else
        *(char *)adr->value = *(char *)mem.var_stack[i].value;
      adr->type = mem.var_stack[i].type;
      free(find);
      free(append);
    }
    i++;
  }
  free(name);
  return (mem.var_stack[0].value);
}

static void equalize(void *adr_op1, int val_op2, t_type type)
{
  if (type == _null)
    return;
  if (type == _char)
    *(char *)adr_op1 = (char)val_op2;
  else if (type == _int)
    *(int *)adr_op1 = val_op2;
}

int equal(char **split, char **words)
{
  void *adr_op1;
  int val_op2;
  int tmp;
  int tmp2;
  t_type type;

  split++;
  type = _null;
  tmp = parseer.words;
  adr_op1 = getAdr(words);
  type = getType(words);
  val_op2 = getVal(words);
  tmp2 = parseer.words;
  parseer.words = tmp;
  adr_op1 = getAdr(words);
  equalize(adr_op1, val_op2, type);
  if (mem.var_stack[0].name)
    adr_op1 = switchString(words[parseer.words]);
  //*(char *)adr_op1 = val_op2;
  parseer.words = tmp2;
  if (words[parseer.words + 1] && !words[parseer.words + 2]
      && words[parseer.words + 1][0] == ')')
    parseer.words++;
  parseer.check = SUCCESS;
  return (*(int *)adr_op1);
}
