#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "Chaussette.h"

t_parseer parseer;
t_ptr varSyn[NB_VAR];
t_ptr boolean_op[3];
t_ptr interrupt[NB_INTER];
t_ptr ptr[NB_OP];

int lookExec(char **split, char **words)
{
  int comp;
  int i;

	comp = 0;
	i = 0;
	testNULL(words);
	while (words[parseer.words][i] == '\t')
		i++;
	while (comp < NB_INTER)
	{
		if (words[parseer.words][i] == interrupt[comp].str[0])
		{
			parseer.check = SUCCESS;
			return (interrupt[comp].fctn(split, words));
		}
		comp++;
	}
	parseer.check = FAILURE;
	return (FAILURE);
}

int parsing(char **split)
{
  char **words;
  int val;

  parseer.words = 0;
  val = 0;
  if (split[parseer.line][0] != '/') 
	{
 		words = strtabParseer(split[parseer.line], ' ');
 		testNULL(words);
  		val = lookExec(split, words);
  		if (parseer.check == FAILURE)
   			perrorPars(words, SYN_ERR);
   		parseer.check = FAILURE;
  		if (parseer.words < my_tablen((const char **)words) - 1 && parseer.cond == FAILURE)
  		{
  			my_puterror("\n(Chaussette) WARNING : too many elements on line : ");
  			my_putnbrfd(parseer.line + 1, 2);
  			my_puterror("\n");
  		}
  		free_tab(words);
	}
	return (val);
}

void initSyntax(void)
{
	varSyn[0].str = "#";
	varSyn[0].var = &fromC;
	varSyn[0].type = &TfromC;
	varSyn[0].struc = &VfromC;
	varSyn[1].str = "$";
	varSyn[1].var = &local;
	varSyn[1].type = &Tlocal;
	varSyn[1].struc = &Vlocal;
	varSyn[2].str = "&";
	varSyn[2].var = &toC;
	varSyn[2].type = &TtoC;
	varSyn[2].struc = &VtoC;
	varSyn[3].str = "";
	varSyn[3].var = &catchInt;
	interrupt[0].str = "=";
	interrupt[0].fctn = &equal;
	interrupt[1].str = "!";
	interrupt[1].fctn = &getFunc;
	interrupt[2].str = "?";
	interrupt[2].fctn = &condHandle;
	ptr[0].str = "+";
	ptr[0].op = &plus;
	ptr[1].str = "-";
	ptr[1].op = &moins;
	ptr[2].str = "*";
	ptr[2].op = &fois;
	ptr[3].str = "/";
	ptr[3].op = &divi;
	ptr[4].str = "%";
	ptr[4].op = &modulo;
	ptr[5].str = "<";
	ptr[5].op = &minus;
	ptr[6].str = "<=";
	ptr[6].op = &minusequ;
	ptr[7].str = ">";
	ptr[7].op = &maxu;
	ptr[8].str = ">=";
	ptr[8].op = &maxuequ;
	ptr[9].str = "==";
	ptr[9].op = &equ;
	ptr[10].str = "&&";
	ptr[10].op = &et;
	ptr[11].str = "||";
	ptr[11].op = &ou;
	ptr[12].str = "!=";
	ptr[12].op = &nequ;
}

int chaussette(char *code, char *name)
{
	char **splitCode;
	int ret;

	
	parseer.in_func = my_strdup(name);
	if (code == NULL)
	{
		parseer.check = FAILURE;
		return (my_puterror("(Chaussette) Warning : No code given.\n"));
	}
	parseer.line = 0;
	splitCode = strtabParseer((const char *)code, ';');
	while (splitCode[parseer.line])
	{
		if (parseer.verbose == 2)
		{
			my_putstr("from C :\n");
			showMem(mem.var_fromC);
			my_putstr("to C :\n");
			showMem(mem.var_toC);
			my_putstr("local :\n");
			showMem(mem.var_local);
		}
		if (parseer.verbose == 1)
		{
			my_putstr(splitCode[parseer.line]);
			my_putchar('\n');
		}
		ret = parsing(splitCode);
		parseer.cond = FAILURE;
		parseer.line++;
	}
	free_tab(splitCode);
	freeVar(mem.var_local);
	mem.var_local = NULL;
	parseer.check = SUCCESS;
	free(parseer.in_func);
	return (ret);
}
