#include "libmy.h"

int isJustInt(char *str)
{
	int i;

	i = 0;
	while (str[i]){
		if (!(str[i] <= '9' && str[i] >= '0') && str[i] != '-'){
			return (0);
		}
		i++;
	}
	return (1);
}

int isJustChar(char *str)
{
	if (my_strlen(str) != 3)
		return (FAILURE);
	if (str[0] == '\'' && str[2] == '\'')
		return (SUCCESS);
	return (FAILURE);
}