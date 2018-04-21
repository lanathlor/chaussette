#ifndef EQUAL_H_
# define EQUAL_H_

#include "Chaussette/chaussette_header/usable.h"

//function
char *getOnlyName(char *words);
int *getAdr(char **words);
int getVal(char **words);
t_type getType(char **words);
int equal(char **split, char **words);
t_var *lookVarForAdrFromName(char *name, char location);

#endif