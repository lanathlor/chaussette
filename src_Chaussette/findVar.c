#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "Chaussette.h"

int *toC(char *var)
{
	int comp;
	int *nb;

	if ((nb = malloc(sizeof(int))) == NULL)
	  my_perror(M_FAIL);
	*nb = 0;
	if ((comp = searchVar(mem.var_toC, var)) != FAILURE)
	{
		free(var);
		return (mem.var_toC[comp].value);
	}
	comp = memLen(mem.var_toC);
	mem.var_toC = memRealloc(mem.var_toC);
  mem.var_toC[comp].name = my_strcpy(mem.var_toC[comp].name, var, SUCCESS);
  if ((mem.var_toC[comp].value = malloc(sizeof(int))) == NULL)
    my_perror(M_FAIL);
  *(int *)mem.var_toC[comp].value = 0;
  mem.var_toC[comp].type = _int;
	return (mem.var_toC[comp].value);
}

int *local(char *var)
{
  int comp;
  int *nb;

  if ((nb = malloc(sizeof(int))) == NULL)
    my_perror(M_FAIL);
  *nb = 0;
  if ((comp = searchVar(mem.var_local, var)) != FAILURE)
    {
      free(nb);
      free(var);
      return (mem.var_local[comp].value);
    }
  comp = memLen(mem.var_local);
  mem.var_local = memRealloc(mem.var_local);
  mem.var_local[comp].name = my_strcpy(mem.var_local[comp].name, var, SUCCESS);
  if ((mem.var_local[comp].value = malloc(sizeof(int))) == NULL)
    my_perror(M_FAIL);
  *(int *)mem.var_local[comp].value = 0;
  mem.var_local[comp].type = _int;
  return (mem.var_local[comp].value);
}

int *fromC(char *var)
{
  int comp;

  if ((comp = searchVar(mem.var_fromC, var)) != FAILURE)
    {
      free(var);
      return (mem.var_fromC[comp].value);
    }
  free(var);
  perrorPars(NULL, "a variable of type '#' on line doesnt exist");
  return (mem.var_fromC[0].value);
}

int *catchInt(char *var)
{
  mem.tmp = my_getnbr(var, FAILURE);
  free(var);
  return (&mem.tmp);
}
