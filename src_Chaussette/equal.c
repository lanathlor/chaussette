#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "Chaussette.h"

t_var *lookVarForAdrFromName(char *name, char location)
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
  mem.var_stack[0].name = NULL;
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
  parseer.words = tmp2;
  if (words[parseer.words + 1] && !words[parseer.words + 2]
      && words[parseer.words + 1][0] == ')')
    parseer.words++;
  parseer.check = SUCCESS;
  return (*(int *)adr_op1);
}
