#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libmy.h"
#include "lipsite.h"

static int codexLen(t_codex *codex)
{
  int i;

  i = 0;
  while (codex[i].type && codex[i].name)
    i++;
  return (i);
}

static void copyCodex(t_codex *new, t_codex *codex)
{
  int i;

  i = 0;
  while (codex[i].type && codex[i].name)
  {
    new[i].type = my_strcpy(new[i].type, codex[i].type, FAILURE);
    new[i].name = my_strcpy(new[i].name, codex[i].name, FAILURE);
    i++;
  }
  new[i].type = NULL;
  new[i].name = NULL;
  new[i + 1].type = NULL;
  new[i + 1].name = NULL;
}

static int findInCodex(t_codex *codex, char *name)
{
  int	i;

  i = 0;
  while (codex[i].type != NULL && codex[i].type != NULL)
    {
      if (my_strcmp(codex[i].type, name) == SUCCESS)
	return (i);
      i++;
    }
  my_putchar('\n');
  my_puterror("(talkative) WARNING : Tag '");
  my_puterror(name);
  return (my_puterror("' not in codex.\n"));
}

static int findInItem(t_item *item, char *name)
{
  int	i;

  i = 0;
  while (item[i].element != NULL && item[i].value != NULL)
    {
      if (my_strcmp(item[i].element, name) == SUCCESS)
	return (i);
      i++;
    }
  my_putchar('\n');
  my_puterror("(talkative) WARNING : Tag '");
  my_puterror(name);
  return (my_puterror("' not set.\n"));
}

static int remplace(char *text, t_codex *codex, int i)
{
  char *get_type;
  int type;

  i++;
  get_type = NULL;
  while (text[i] != '%')
    {
    	if (!text[i])
    		my_perror("(talkative) Error: missing a '%' in the line.");
      get_type = my_reallocItem(get_type, text[i]);
      i++;
    }
  if ((type = findInCodex(codex, get_type)) == FAILURE)
    return (FAILURE);
  my_putstr(codex[type].name);
  free(get_type);
  return (i);
}

static int stepByStep(t_item *item, t_codex *codex)
{
  char *text;
  int i;
  int findRet;

  text = NULL;
  i = 0;
  if ((findRet = findInItem(item, "text")) == FAILURE)
    return (FAILURE);
  text = my_strcpy(text, item[findRet].value, FAILURE);
  while (text[i])
    {
      if (text[i] != '%')
	{
	  my_putchar(text[i]);
	  i++;
	}
      else
	{
	  if ((i = remplace(text, codex, i)) == FAILURE)
	    return (FAILURE);
	  i++;
	}
    }
  free(text);
  return (SUCCESS);
}

/////////// EXTERIOR FUNCTION ////////////////
t_codex *initCodex(char *types, ...)
{
	int i;
	char **types_separets;
  t_codex *codex;

	va_list(ap);
	i = 0;
	types_separets = my_strtab(types);
	va_start(ap, types);
  if ((codex = malloc(sizeof(codex) * (my_tablen((const char **)types_separets) + 3))) == NULL)
    my_perror(M_FAIL);
	while (types_separets[i])
	{
		codex[i].type = my_strcpy(codex[i].type, types_separets[i], SUCCESS);
		codex[i].name = my_strcpy(codex[i].name, va_arg(ap, char *), FAILURE);
		i++;
	}
 	codex[i].type = NULL;
	codex[i].name = NULL;
	va_end(ap);
  free(types_separets);
  return (codex);
}

t_codex *addInCodex(t_codex *codex, char *type, char *name)
{
  t_codex *new;

  if ((new = malloc(sizeof(t_codex) * (codexLen(codex) + 3))) == NULL)
    my_perror(M_FAIL);
  copyCodex(new, codex);
  freeCodex(codex);
  new[codexLen(new)].type = my_strcpy(new[codexLen(new)].type, type, FAILURE);
  new[codexLen(new)].name = my_strcpy(new[codexLen(new)].name, name, FAILURE);
  new[codexLen(new) + 1].type = NULL;
  new[codexLen(new) + 1].type = NULL;
  return (new);
}

void freeCodex(t_codex *codex)
{
  int	i;

  i = ZERO;
  if (codex != NULL)
    {
      while (codex[i].type || codex[i].name)
	{
	  if (my_strlen(codex[i].type) > 0)
	    {
	      free (codex[i].type);
	      codex[i].type = NULL;
	    }
	  if (my_strlen(codex[i].name) > 0)
	    {
	      free(codex[i].name);
	      codex[i].name = NULL;
	    }
	  i++;
	}
    }
}

int talkative(t_item *item, t_codex *codex)
{
  if (item == NULL)
    return (my_puterror("(talkative) WARNING : item given is NULL.\n"));
  if (codex == NULL)
    return (my_puterror("(talkative) WARNING : codex given is NULL.\n"));
  if (stepByStep(item, codex) == FAILURE)
    return (FAILURE);
  my_putchar('\n');
  return (0);
}
