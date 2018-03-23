#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "lipsite.h"
#include "Chaussette.h"

static t_var *memFill(t_var *var, t_var *new)
{
	int i;
	int len;

	i = 0;
	while (new[i].name)
	{
		len = memLen(var);
		var = memRealloc(var);
		var[len].name = my_strcpy(var[len].name, new[i].name, FAILURE);
  		if ((var[len].value = malloc(sizeof(int))) == NULL)
       		my_perror(M_FAIL);
       	if (new[i].type == _int)
	  		*(int *)var[len].value = *(int *)new[i].value;
	  	else
	  		*(char *)var[len].value = *(char *)new[i].value;
  		var[len].type = new[i].type;
  		var[len + 1].name = NULL;
  		var[len + 1].value = 0;
  		var[len + 1].type = _null;
		i++;
	}
	return (var);
}

int change_name(t_var *var, char *name, int i)
{
	char *append;
	int len;

	len = my_strlen(var[i].name);
	free(var[i].name);
	var[i].name = my_strcpy(var[i].name, name, FAILURE);
	i++;
	while (var[i].name && my_strcmp(var[i].name, "__split") == FAILURE)
	{
		append = my_hashstr(var[i].name, len, my_strlen(var[i].name), FAILURE);
		var[i].name = my_strcpy(var[i].name, name, FAILURE);
		var[i].name = my_strcat(var[i].name, append, FAILURE);
		i++;
	}
	return (i);
}

static t_var *dumpLLocal(t_var *var, char *var_name)
{
	int inc;
	int i;
	char **name;

	i = 0;
	inc = 0;
	if ((name = strtabParseer(var_name, ' ')) == NULL)
		perrorPars(NULL, "Stop on delimitation");
	while (name[inc])
	{
		i = change_name(var, name[inc], i);
		// else
		// {
		// 	free(var[i].name);
		// 	var[i].name = my_strcpy(var[i].name, name[inc], FAILURE);
		// }
		i++;
		inc++;
	}
	return (var);
}

static t_var *compArg(char **words)
{
	char **arg;
	t_var *var;
	int tmp;
	int len;

	parseer.words++;
	if (!words[parseer.words])
		return (NULL);
	if (words[parseer.words][0] != '(')
		perrorPars(words, "A parenthese is needed here");
	testNULL(words);
	if ((arg = malloc(sizeof(char *))) == NULL)
		my_perror(M_FAIL);
	if ((var = malloc(sizeof(t_var) * 1)) == NULL)
		perrorPars(words, M_FAIL);
	var[0].name = NULL;
	arg[0] = NULL;
	while (words[parseer.words + 1] && words[parseer.words + 1][0] != ')')
		{
			if (my_strcmp(words[parseer.words + 1], "=") == SUCCESS)
				{
					parseer.words++;
					tmp = equal(NULL, words);
					len = memLen(var);
					var = memRealloc(var);
					var[len].name = my_strcpy(var[len].name, "simple_int", FAILURE);
					if ((var[len].value = malloc(sizeof(int))) == NULL)
       					my_perror(M_FAIL);
					*(int *)var[len].value =  tmp;
					var[len].type = _int;
					var[len + 1].name = NULL;
				}
			else
			{
				tmp = getVal(words);
				if (parseer.string)
					var = memFill(var, getVarFromPart(words));
				len = memLen(var);
				var = memRealloc(var);
				var[len].name = my_strcpy(var[len].name, "simple_int", FAILURE);
				if ((var[len].value = malloc(sizeof(int))) == NULL)
					my_perror(M_FAIL);
				*(int *)var[len].value =  tmp;
				var[len].type = _int;
				var[len + 1].name = NULL;
			}
			len = memLen(var);
			var = memRealloc(var);
			var[len].name = my_strcpy(var[len].name, "__split", FAILURE);
			if ((var[len].value = malloc(sizeof(int))) == NULL)
       			my_perror(M_FAIL);
			*(int *)var[len].value =  0;
			var[len].type = _int;
			var[len + 1].name = NULL;
			//arg = reallocTab(arg, my_getstr(tmp));
		}
	parseer.words++;
	testNULL(words);
	if (words[parseer.words][0] != ')')
		perrorPars(words, "A parenthese is needed here");
	return (var);
}

static t_item *haveFunc(char **words, t_item *item)
{
	int inc;

	inc = 0;
	parseer.words++;
	testNULL(words);
	setItemInfo("name", words[parseer.words]);
	while (parseer.items && parseer.items[inc]){
		if (my_strcmp(InItem(parseer.items[inc], "name"), words[parseer.words]) == SUCCESS)
			return (parseer.items[inc]);
		inc++;
	}
	inc = 0;
	if (parseer.include == NULL || parseer.include[0] == NULL)
		perrorPars(words, "There is no function file loaded");
	while (parseer.include[inc])
	{
		item = createItem();
		setFileLink(parseer.include[inc]);
		if ((item = findItem(item)) != NULL)
			return (item);
		freeItem(item);
		inc++;
	}
	freeInfo();
	perrorPars(words, "is not referenced as an existant function");
	return (NULL);
}

static void setBuiltIn(t_ptr *built_in)
{
	built_in[0].str = "write";
	built_in[0].ptr = &writeChaussette;
	built_in[1].str = "ascii";
	built_in[1].ptr = &asciiChaussette;
	built_in[2].str = "writeAt";
	built_in[2].ptr = &writeChaussetteAt;
	built_in[3].str = "asciiAt";
	built_in[3].ptr = &asciiChaussetteAt;
	built_in[4].str = "return";
	built_in[4].ptr = &returning;
	built_in[5].str = "read";
	built_in[5].ptr = &readFrom;
	built_in[6].str = "string";
	built_in[6].ptr = &setString;
}

static int execBuiltIn(char **split, char **words, t_ptr *built_in)
{
	int inc;

	inc = 0;
	while(inc != NB_BUILT)
	{
		if (my_strcmp(built_in[inc].str, words[parseer.words + 1]) == SUCCESS)
			return (built_in[inc].ptr(split, words));
		inc++;
	}
	parseer.check = FAILURE;
	return (FAILURE);
}

int getFunc(char **split, char **words)
{
	t_item *item;
	t_var *var;
	t_var *new;
	t_ptr built_in[NB_BUILT];
	int keep_line;
	int keep_word;
	int keep_cond;
	int ret;
	char *keep_func;
	char *func_name;

	item = NULL;
	testNULL(words);
	setBuiltIn(built_in);
	ret = execBuiltIn(split, words, built_in);
	if (parseer.check == FAILURE)
	{
		if ((var = malloc(sizeof(t_var) * (memLen(mem.var_local) + 2))) == NULL)
			perrorPars(words, M_FAIL);
		item = haveFunc(words, item);
		func_name = my_strdup(words[parseer.words]);
		new = compArg(words);
		if (memCopy(var, mem.var_local) == FAILURE)
			perrorPars(words, "Copy failed");
		var[memLen(mem.var_local)].name = NULL;
		keep_func = my_strdup(parseer.in_func);
		keep_line = parseer.line;
		keep_word = parseer.words;
		keep_cond = parseer.cond;
		if ((mem.var_local = malloc(sizeof(t_var) * (memLen(new) + 2))) == NULL)
			perrorPars(words, M_FAIL);
		memCopy(mem.var_local, dumpLLocal(new, InItem(item, "arguments")));
		if (parseer.verbose)
		{
			my_putstr("\nFunction : ");
			my_putstr(InItem(item, "name"));
			my_putstr("\n");
		}
		if (parseer.verbose == 2)
		{
			showMem(mem.var_local);
		}
		ret = chaussette(InItem(item, "function"), func_name);
		if ((mem.var_local = malloc(sizeof(t_var) * (memLen(var) + 2))) == NULL)
			perrorPars(words, M_FAIL);
		if (memCopy(mem.var_local, var) == FAILURE)
			perrorPars(words, "Copy Failed");
		mem.var_local[memLen(var)].name = NULL;
		parseer.line = keep_line;
		parseer.words = keep_word;
		parseer.cond = keep_cond;
		freeVar(var);
		freeVar(new);
		freeInfo();
		if (parseer.verbose)
		{
			my_putstr("\nexit function : ");
			my_putstr(InItem(item, "name"));
			my_putstr("\n");
		}
		if (parseer.verbose == 2)
		{
			showMem(mem.var_local);
		}
		freeItem(item);
		parseer.in_func = my_strdup(keep_func);
		free(keep_func);
		free(func_name);
	}
	parseer.check = SUCCESS;
	return (ret);
}