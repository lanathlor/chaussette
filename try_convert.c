// #include <stdlib.h>
// #include <unistd.h>
// #include "libmy.h"
// #include "Chaussette.h"

// char **addStack(char **stack, char *str);

// void fullyDestack(char **tab, int new, char **stack)
// {
// 	int len;

// 	len = my_tablen((const char **)stack) - 1;
// 	while (len >= 0)
// 	{
// 		new = destack(stack, tab, new);
// 		len--;
// 	}
// }

// int destackFromPar(char **tab, char **stack, int new)
// {
// 	int len;

// 	len = my_tablen((const char **)stack) - 1;
// 	while (stack[len][0] != ')')
// 	{
// 		new = destack(stack, tab, new);
// 		len--;
// 	}
// 	new = destack(stack, tab, new);
// 	stack[len] = NULL;
// 	return (new);
// }

// int destack(char **stack, char **tab, int new)
// {
// 	int len;

// 	len = my_tablen((const char **)stack) - 1;
// 	if (stack[len][0] == ')')
// 		tab[new] = my_strcpy(tab[new], stack[len], FAILURE);
// 	stack[len] = NULL;
// 	return (new--);
// }

// int prior(char op, char c)
// {
// 	if (op == '*' || op == '/')
// 		op = 1;
// 	else
// 		op = 0;
// 	if (c == '*' || c == '/')
// 		c = 1;
// 	else
// 		c = 0;
// 	return ((op % 2 + c % 2) % 2);
// }

// int analyze(char **tab, char **stack, int new, char *str)
// {
// 	int len;

// 	len = my_tablen((const char **)stack) - 1;
// 	if (len == 0 || stack[len][0] == ')' || prior(stack[len][0], str[0]))
// 		stack = addStack(stack, str);
// 	else
// 	{
// 		new = destack(stack, tab, new);
// 		stack = addStack(stack, str);
// 	}
// 	return (new);
// }

// char **addStack(char **stack, char *str)
// {
// 	stack = reallocTab(stack, str);
// 	return(stack);
// }

// int isOperand(char *c)
// {
// 	if (c[0] == '+' || c[0] == '-' || c[0] == '*' || c[0] == '/' || c[0] == ')' || c[0] == '(')
// 		return (FAILURE);
// 	return (SUCCESS);
// }

// char **convertNP(char **tmp, char **stack)
// {
// 	char **tab;
// 	int inc;
// 	int new;

// 	inc = my_tablen((const char **)tmp) - 1;
// 	tab = malloc(inc + 1);
// 	tab[inc + 1] = 0;
// 	new = inc;
// 	while (inc >= 0)
// 	{ 
// 		my_putstr(tmp[inc]);
// 		if (isOperand(tmp[inc]) == SUCCESS)
// 		{
// 			tab[new] = my_strcpy(tab[new], tmp[inc], FAILURE);
// 			new--;
// 		}
// 		else if (tmp[inc][0] == ')')
// 			stack = addStack(stack, tmp[inc]);
// 		else if (tmp[inc][0] == '(')
// 			new = destackFromPar(tab, stack, new);
// 		else if (isOperand(tmp[inc]) == FAILURE)
// 			new = analyze(tab, stack, new, tmp[inc]);
// 		inc--;
// 	}
// 	fullyDestack(tab, new, stack);
// 	return (tab);
// }

// int main(int argc, char **argv)
// {
// 	char **stack;
// 	char **tmp;
// 	char **tab;

// 	stack = malloc(1);
// 	stack[0] = NULL;
// 	tmp = strtabParseer(argv[1], ' ');
// 	tab = convertNP(tmp, stack);
// 	my_puttab((const char **)tab);
// 	free_tab(tmp);
// 	free_tab(tab);
// 	return (SUCCESS);
// }