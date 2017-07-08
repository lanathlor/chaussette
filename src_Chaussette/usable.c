#include <unistd.h>
#include <stdlib.h>
#include "libmy.h"
#include "Chaussette.h"

// gestion parsing //

static char	*my_reallocParseer(char *str, char buff)
{
  char	*tmp;
  int	i;

  if ((tmp = malloc(my_strlen(str) + TWO)) == NULL)
    my_perror(M_FAIL);
  i = ZERO;
  if (str != NULL)
    while (str[i] != '\0')
      {
	tmp[i] = str[i];
	i = i + ONE;
      }
    tmp[i] = buff;
    tmp[i + ONE] = '\0';
    free(str);
    return (tmp);
}

char	*gnlParseer(int fd)
{
  char		*str;
  char		buff;

  buff = ZERO;
  str = NULL;
  while (read(fd, &buff, ONE) > ZERO && buff != ';')
    {
      if (buff != '\n')
	str = my_reallocParseer(str, buff);
    }
  if (my_strlen(str) > ZERO)
    str = my_reallocParseer(str, ';');
  return (str);
}

////// strtab ////////

static int  is_alpha(char c, char delim)
{
  if (c == ZERO)
    return (SUCCESS);
  if (c != delim)
    return (SUCCESS);
  return (FAILURE);
}

static char **my_strtowordtab(const char *str, char **word, char delim)
{
  int   i;
  int   s;

  i = ZERO;
  s = ZERO;
  while (str[s])
    {
      if (is_alpha(str[s], delim) == SUCCESS)
         word[i] = my_realloc(word[i], str[s++]);
      else
      {
        while (is_alpha(str[s++], delim) == FAILURE)
         ;
       s--;
       if (my_strlen(word[i]) >= 1)
            i++;
       }
    }
  word[i + ONE] = ZERO;
  return (word);
}

static char **my_compressor(char **tab, int i)
{
  if (!tab[i + ONE])
    {
      tab[i] = NULL;
      return (tab);
    }
  i++;
  while (tab[i] && tab[i + ONE])
    {
      tab[i - ONE] = my_strcpy(tab[i - ONE], tab[i], FAILURE);
      i++;
    }
  tab[i - ONE] = NULL;
  return (tab);
}

char  **strtabParseer(const char *str, char delim)
{
  int i;
  char  **tab;

  i = ZERO;
  tab = NULL;
  tab = tab_malloc(my_strlen(str));
  tab = my_strtowordtab(str, tab, delim);
  while (tab[i])
    {
      if (tab[i][ZERO] == ZERO)
  {
    if ((tab = my_compressor(tab, i)) == NULL)
      return (NULL);
    i = ZERO;
  }
      else
  i++;
    }
  return (tab);
}

void perrorPars(char **word, char *errorType)
{
  my_puterror("(Chaussette) ERROR on line ");
  my_putnbrfd(parseer.line + 1, 2);
  my_puterror(" : ");
  if (word)
  {
    my_puterror("'");
    my_puterror(word[parseer.words]);
    my_puterror("' ");
    free_tab(word);
  }
  my_puterror(errorType);
  my_puterror(".\n");
  freeMem();
  my_putstr("\npress enter to exit\n");
  free(gnl(0));
  exit(FAILURE);
}

// gestion memoire //

int memLen(t_var *var)
{
  int i;

  i = 0;  
  if (var == NULL)
    return (0);
  while (var[i].name)
    i++;
  return(i);
}

int memCopy(t_var *new, t_var *var)
{
  int i;

  i = 0;
  if (var == NULL)
    return (FAILURE);
  while (var[i].name)
  {
    new[i].name = my_strcpy(new[i].name, var[i].name, FAILURE);
    if ((new[i].value = malloc(sizeof(int))) == NULL)
          my_perror(M_FAIL);
    if (var[i].type == _char)
      *(char *)new[i].value = *(char *)var[i].value;
    else
      *(int *)new[i].value = *(int *)var[i].value;
    new[i].type = var[i].type;
    i++;
  }
  new[i].name = NULL;
  new[i].value = 0;
  new[i].type = _null;
  return (SUCCESS);
}

t_var *memRealloc(t_var *var)
{
  t_var *new;

  if ((new = malloc(sizeof(t_var) * (memLen(var) + 2))) == NULL)
    my_perror(M_FAIL);
  memCopy(new, var);
  freeVar(var);
  new[memLen(new) + 1].name = NULL;
  new[memLen(new) + 1].value = 0;
  new[memLen(new) + 1].type = _null;
  return (new);
}

int searchVar(t_var *var, char *name)
{
  int i;

  i = 0;
  while (var[i].name)
  {
    if (my_strcmp(var[i].name, name) == SUCCESS)
      return (i);
    i++;
  }
  return (FAILURE);
}

void testNULL(char **words)
{
  if (!words[parseer.words])
  {
    parseer.words--;
    perrorPars(words, EMPTY_STR);
  }
}

t_var *memAdd(t_var *var, t_var add)
{
  t_var *new;
  int   tmp;
  int   len;

  if ((new = malloc(sizeof(t_var) * (memLen(var) + 2))) == NULL)
    my_perror(M_FAIL);
  memCopy(new, var);
  freeVar(var);
  len = memLen(new);
  new[len].name = my_strcpy(new[len].name, add.name, FAILURE);
  if ((new[len].value = malloc(sizeof(int))) == NULL)
        my_perror(M_FAIL);
  if (add.type == _int)
    *(int *)new[len].value = *(int *)add.value;
  else
    *(char *)new[len].value = *(char *)add.value;
  new[len].type = add.type;
  new[len + 1].name = NULL;
  new[len + 1].value = 0;
  new[len + 1].type = _null;
  return (new);
}

// gestion function //
