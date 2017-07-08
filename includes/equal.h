#ifndef EQUAL_H_
# define EQUAL_H_

#include "usable.h"

//function
char *getOnlyName(char *words, char **parse);
int *getAdr(char **words);
int getVal(char **words);
t_type getType(char **words);
int equal(char **split, char **words);

#endif