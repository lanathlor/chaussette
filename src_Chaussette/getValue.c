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
			while (words[i] != ']'){
			  	if (!words[i])
			  		perrorPars(NULL, "you need to close the braket");
				i++;
			}
		}
		else if (words[i] != ',')
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