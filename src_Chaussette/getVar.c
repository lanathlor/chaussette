#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "Chaussette.h"

t_var *VtoC(char *var)
{
	int comp;
	int *nb;

	if ((nb = malloc(sizeof(int))) == NULL)
	  my_perror(M_FAIL);
	*nb = 0;
	if ((comp = searchVar(mem.var_toC, var)) != FAILURE)
		return (&mem.var_toC[comp]);
	comp = memLen(mem.var_toC);
	mem.var_toC = memRealloc(mem.var_toC);
  mem.var_toC[comp].name = my_strcpy(mem.var_toC[comp].name, var, FAILURE);
  if ((mem.var_toC[comp].value = malloc(sizeof(int))) == NULL)
    my_perror(M_FAIL);
  *(int *)mem.var_toC[comp].value = 0;
  mem.var_toC[comp].type = _int;
	return (&mem.var_toC[comp]);
}

t_var *Vlocal(char *var)
{
  int comp;
  int *nb;

  if ((nb = malloc(sizeof(int))) == NULL)
    my_perror(M_FAIL);
  *nb = 0;
  if ((comp = searchVar(mem.var_local, var)) != FAILURE)
      return (&mem.var_local[comp]);
  comp = memLen(mem.var_local);
  mem.var_local = memRealloc(mem.var_local);
  mem.var_local[comp].name = my_strcpy(mem.var_local[comp].name, var, FAILURE);
  if ((mem.var_local[comp].value = malloc(sizeof(int))) == NULL)
    my_perror(M_FAIL);
  *(int *)mem.var_local[comp].value = 0;
  mem.var_local[comp].type = _int;
  return (&mem.var_local[comp]);
}

t_var *VfromC(char *var)
{
  int comp;

  if ((comp = searchVar(mem.var_fromC, var)) != FAILURE)
      return (&mem.var_fromC[comp]);
  return (&mem.var_fromC[0]);
}

t_var *getVar(char **words)
{
  char *hash;
  t_var *var;
  int comp;

  testNULL(words);
  comp = 0;
  var = NULL;
  hash = getOnlyName(words[parseer.words]);
  while (comp < NB_VAR)
    {
      if (words[parseer.words][0] == varSyn[comp].str[0])
		{
		  parseer.check = SUCCESS;
		  var = varSyn[comp].struc(hash); 
	  	  return (var);
		}
      comp++;
    }
  free(hash);
  parseer.check = FAILURE;
  return (var);
}

static t_var *getAll(t_var *var, char loc, char *name)
{
	if (loc == '#')
		var = findFromC(var, name);
	else if (loc == '&')
		var = findToC(var, name);
	else if (loc == '$')
		var = findLocal(var, name);
	else
		perrorPars(NULL, SYN_ERR);
	return (var);
}

t_var *getVarFromPart(char **words)
{
	char *name;
	char *name_array;
	char *name_struct;
	t_var *var;

	if ((var = malloc(sizeof(t_var) * 2)) == NULL)
		perrorPars(words, M_FAIL);
	var[0].name = NULL;
	name = my_hashstr(words[parseer.words], 1, my_strlen(words[parseer.words]), FAILURE);
	name_array = my_strcpy(name, "[", FAILURE);
	name_struct = my_strcpy(name, ".", FAILURE);
	if (words[parseer.words][0] == '.')
	{
		var[0].name = my_strcpy(var[0].name, "simple_int", FAILURE);
		if ((var[0].value = malloc(sizeof(int))) == NULL)
	       		my_perror(M_FAIL);
		*(int *)var[0].value = my_getnbr(name, FAILURE);
		var[0].type = _int;
		var[1].name = NULL;
	}
	else
	{
		var = getAll(var, words[parseer.words][0], name);
		var = getAll(var, words[parseer.words][0], name_array);
		var = getAll(var, words[parseer.words][0], name_struct);
	}
	free(name);
	free(name_array);
	free(name_struct);
	return (var);	
}

t_var *getVarFromPartName(char *var_name)
{
	char *name;
	char *name_array;
	char *name_struct;
	t_var *var;

	if ((var = malloc(sizeof(t_var) * 2)) == NULL)
		perrorPars(NULL, M_FAIL);
	var[0].name = NULL;
	name = my_hashstr(var_name, 1, my_strlen(var_name), FAILURE);
	name_array = my_strcpy(name, "[", FAILURE);
	name_struct = my_strcpy(name, ".", FAILURE);
	if (var_name[0] == '.')
	{
		var[0].name = my_strcpy(var[0].name, "simple_int", FAILURE);
		if ((var[0].value = malloc(sizeof(int))) == NULL)
	       		my_perror(M_FAIL);
		*(int *)var[0].value = my_getnbr(name, FAILURE);
		var[0].type = _int;
		var[1].name = NULL;
	}
	else
	{
		var = getAll(var, var_name[0], name);
		var = getAll(var, var_name[0], name_array);
		var = getAll(var, var_name[0], name_struct);
	}
	free(name);
	free(name_array);
	free(name_struct);
	return (var);	
}