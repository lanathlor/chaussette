#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "Chaussette.h"

t_mem mem;

// gestion memoire //

void showMem(t_var *var)
{
  int i;

  i = 0;
  my_putstr("Mem :\n");
  while (var[i].name)
  {
    my_putstr("\tname = ");
    my_putstr(var[i].name);
    my_putstr(", value = ");
    if (var[i].type == _char)
    {
      my_putnbr(*(char *)var[i].value);
      my_putstr(", char\n");
    }
    else if (var[i].type == _string)
    {
      my_putnbr(*(int *)var[i].value);
      my_putstr(", string\n");
    }
    else
    {
      my_putnbr(*(int *)var[i].value);
      my_putstr(", int\n");
    }
    i++;
  }
}

void showAllMem(void)
{
    my_putstr("to C :\n");
    showMem(mem.var_toC);
    my_putstr("from C :\n");
    showMem(mem.var_fromC);
}

void initMem(void)
{
  if ((mem.var_fromC = malloc(sizeof(t_var) * 1)) == NULL)
    my_perror(M_FAIL);
  if ((mem.var_toC = malloc(sizeof(t_var) * 1)) == NULL)
    my_perror(M_FAIL);
  if ((mem.var_local = malloc(sizeof(t_var) * 1)) == NULL)
    my_perror(M_FAIL);
  if ((mem.var_stack = malloc(sizeof(t_var) * 1)) == NULL)
    my_perror(M_FAIL);
  mem.tmp = 0;
  mem.var_fromC[0].name = NULL;
  mem.var_toC[0].name = NULL;
  mem.var_local[0].name = NULL;
  mem.var_stack[0].name = NULL;
  parseer.verbose = 0;
  initSyntax();
}

int freeVar(t_var *var)
{
  int i;

  if (var == NULL)
    return (FAILURE);
  i = 0;
  while (var[i].name)
  {
    if (var[i].name != NULL)
//	   free(var[i].name);
 //   var[i].name = NULL;
//    free(var[i].value);
  //  var[i].value = NULL;
    i++;
  }
  if (var)
    free(var);
  var = NULL;
  return (SUCCESS);
}

int freeStack(t_stack *stack)
{
  (void) stack;
  return (SUCCESS);
}

void freeMem(void)
{
  if (mem.var_fromC)
    freeVar(mem.var_fromC);
  if (mem.var_toC)
    freeVar(mem.var_toC);
  if (mem.stack)
    freeStack(mem.stack);
  if (mem.var_local)
    freeVar(mem.var_local);
  if (parseer.include)
    free_tab(parseer.include);
}

void addInt(int *nb, char *name)
{
  int len;

  len = memLen(mem.var_fromC);
  mem.var_fromC = memRealloc(mem.var_fromC);
  mem.var_fromC[len].name = my_strcpy(mem.var_fromC[len].name, name, FAILURE);
  if ((mem.var_fromC[len].value = malloc(sizeof(int))) == NULL)
      perrorPars(NULL, M_FAIL);
  mem.var_fromC[len].value = (int *)nb;
  mem.var_fromC[len].type = _int;
  mem.var_fromC[len + 1].name = NULL;
  mem.var_fromC[len + 1].type = _null;
}

void addChar(char *nb, char *name)
{
  int len;

  len = memLen(mem.var_fromC);
  mem.var_fromC = memRealloc(mem.var_fromC);
  mem.var_fromC[len].name = my_strcpy(mem.var_fromC[len].name, name, FAILURE);
  if ((mem.var_fromC[len].value = malloc(sizeof(char))) == NULL)
      perrorPars(NULL, M_FAIL);
  mem.var_fromC[len].value = (char *)nb;
  mem.var_fromC[len].type = _char;
  mem.var_fromC[len + 1].name = NULL;
  mem.var_fromC[len + 1].type = _null;
}

static char *makeVarHappen(char *var, char *name, char *i)
{
  int inc;

  inc = 0;
  while (name[inc])
    {
      var = my_realloc(var, name[inc]);
      inc++;
    }
  inc = 0;
  var = my_realloc(var, '[');
  while (i[inc])
    {
      var = my_realloc(var, i[inc]);
      inc++;
    }
  var = my_realloc(var, ']');
  return (var);
}

static void addPtr(int nb, char *name)
{
  int len;

  len = memLen(mem.var_fromC);
  mem.var_fromC = memRealloc(mem.var_fromC);
  mem.var_fromC[len].name = my_strcpy(mem.var_fromC[len].name, name, FAILURE);
  if ((mem.var_fromC[len].value = malloc(sizeof(int))) == NULL)
      perrorPars(NULL, M_FAIL);
  *(int *)mem.var_fromC[len].value = nb;
  mem.var_fromC[len].type = _string;
}

void addStr(char *str, char *name)
{
  int inc;
  char *var;
  char *i;

  inc = 0;
  i = NULL;
  addPtr(my_strlen(str), name);
  while (str[inc])
    {
      if ((var = malloc(sizeof(char) * 1)) == NULL)
	      perrorPars(NULL, M_FAIL);
      var[0] = 0;
      i = my_getstr(inc);
      var = makeVarHappen(var, name, i);
      addChar((char *)&str[inc], var);
      if (i && i[0] != '0')
        free (i);
      free(var);
      inc++;
    }
  if ((var = malloc(sizeof(char) * 1)) == NULL)
    perrorPars(NULL, M_FAIL);
  var[0] = 0;
  i = my_getstr(inc);
  var = makeVarHappen(var, name, i);
  addChar((char *)&str[inc], var);
  if (i && i[0] != '0')
    free (i);
  free(var);
}

int *getInt(char *name)
{
  int i;

  i = 0;
  while (mem.var_toC[i].name)
    {
      if (my_strcmp(name, mem.var_toC[i].name) == SUCCESS)
	return (mem.var_toC[i].value);
      i++;
    }
  return (NULL);
}

// gestion fonction //

void readLeadFile(char *file)
{
	int fd;
	char *str;

	if (!file)
		file = "./leadfile.cht";
	if ((fd = open(file, O_RDONLY)) == FAILURE)
		my_perror(O_FAIL);
	if ((parseer.include = malloc(sizeof (char *))) == NULL)
		my_perror(M_FAIL);
	parseer.include[0] = NULL;
	str = gnl(fd);
	while (my_strcmp(str, "FILE FUNCTION START") == FAILURE && str != NULL)
	{
		free(str);
		str = gnl(fd);
	}
	str = gnl(fd);
	while (my_strcmp(str, "FILE FUNCTION END") == FAILURE && str != NULL)
	{
		if (str[0] != '/')
			parseer.include = reallocTab(parseer.include, str);
		free(str);
		str = gnl(fd);
	}
	free(str);
	close(fd);
}
