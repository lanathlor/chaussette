#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "Chaussette.h"

static int partstrcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] || !str2[i])
		return (SUCCESS);
	return (FAILURE);
}

t_var *findFromC(t_var *var, char *name)
{
	int i;

	i = 0;
	while (mem.var_fromC[i].name != NULL)
	{
		if (partstrcmp(mem.var_fromC[i].name, name) == SUCCESS)
			var = memAdd(var, mem.var_fromC[i]);
		i++;
	}
	return (var);
}

t_var *findToC(t_var *var, char *name)
{
	int i;

	i = 0;
	while (mem.var_toC[i].name != NULL)
	{
		if (partstrcmp(mem.var_toC[i].name, name) == SUCCESS)
			var = memAdd(var, mem.var_toC[i]);
		i++;
	}
	return (var);
}

t_var *findLocal(t_var *var, char *name)
{
	int i;

	i = 0;
	while (mem.var_local[i].name != NULL)
	{
		if (partstrcmp(mem.var_local[i].name, name) == SUCCESS)
			var = memAdd(var, mem.var_local[i]);
		i++;
	}
	return (var);
}

