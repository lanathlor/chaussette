#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "Chaussette.h"

t_type TtoC(char *var)
{
	int comp;
	int *nb;

	if ((nb = malloc(sizeof(int))) == NULL)
	  my_perror(M_FAIL);
	*nb = 0;
	if ((comp = searchVar(mem.var_toC, var)) != FAILURE)
	{
		free(var);
		return (mem.var_toC[comp].type);
	}
	comp = memLen(mem.var_toC);
	mem.var_toC = memRealloc(mem.var_toC);
  mem.var_toC[comp].name = my_strcpy(mem.var_toC[comp].name, var, SUCCESS);
  mem.var_toC[comp].value = nb;
  mem.var_toC[comp].type = _int;
	return (mem.var_toC[comp].type);
}

t_type Tlocal(char *var)
{
  int comp;
  int *nb;

  if ((nb = malloc(sizeof(int))) == NULL)
    my_perror(M_FAIL);
  *nb = 0;
  if ((comp = searchVar(mem.var_local, var)) != FAILURE)
    {
      free(var);
      free(nb);
      return (mem.var_local[comp].type);
    }
  comp = memLen(mem.var_local);
  mem.var_local = memRealloc(mem.var_local);
  mem.var_local[comp].name = my_strcpy(mem.var_local[comp].name, var, SUCCESS);
  mem.var_local[comp].value = nb;
  mem.var_local[comp].type = _int;
  return (mem.var_local[comp].type);
}

t_type TfromC(char *var)
{
  int comp;

  if ((comp = searchVar(mem.var_fromC, var)) != FAILURE)
    {
      free(var);
      return (mem.var_fromC[comp].type);
    }
  free(var);
  perrorPars(NULL, "a variable of type '#' on line doesnt exist");
  return (mem.var_fromC[0].type);
}