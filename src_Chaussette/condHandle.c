#include <stdlib.h>
#include "libmy.h"
#include "Chaussette.h"

static int isElseIf(char **split)
{
	char *str;
	char **words;

	str = my_hashstr(split[parseer.line], 2, 8, FAILURE);
	if (my_strcmp(str, "elseif") == SUCCESS)
	{
		parseer.words = 2;
		words = strtabParseer(split[parseer.line], ' ');
 		if (getVal(words))
 		{
 			free_tab(words);
			free(str); 			
 			return(SUCCESS);
 		}
 		free_tab(words);
	}
	free(str);
	return (FAILURE);
}

static int goInIf(char **split)
{
	int ret;

	ret = 0;
	parseer.line++;
	while (split[parseer.line] && my_strcmp(split[parseer.line], "? endif") != SUCCESS && split[parseer.line][0] != '#')
	{
		ret = parsing(split);
		parseer.line++;
	}
	while (split[parseer.line] && my_strcmp(split[parseer.line], "? endif") != SUCCESS)
		parseer.line++;
	parseer.check = SUCCESS;
	return (ret);
}

static int findOtherStatment(char **split)
{
	size_t nest;

	nest = 0;
	parseer.line++;
	while (split[parseer.line] && (my_strcmp(split[parseer.line], "? endif") != SUCCESS || nest))
	{
		if (my_strcmp(split[parseer.line], "? endif") == SUCCESS){
			if (nest != 0)
				nest--;
		} else if (split[parseer.line][0] == '?') {
			nest++;
		}
		if (my_strcmp(split[parseer.line], "# else") == SUCCESS)
			return (goInIf(split));
		else if (isElseIf(split) == SUCCESS)
			return (goInIf(split));
		parseer.line++;
	}
	parseer.check = SUCCESS;
	return (0);
}

int condHandle(char **split, char **words)
{
	int val;

	parseer.words++;
	parseer.cond = SUCCESS;
	val = 0;
	testNULL(words);
	if (my_strcmp(words[parseer.words], "if") == FAILURE)
	{
		parseer.check = FAILURE;
		return (FAILURE);
	}
	val = getVal(words);
	if (val == 1)
		return (goInIf(split));
	return (findOtherStatment(split));	
}