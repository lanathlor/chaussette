#ifndef CHAUSSETTE_H_
# define CHAUSSETTE_H_

#include "usable.h"
#include "equal.h"
#include "findVar.h"
#include "findType.h"
#include "getVar.h"
#include "getFunc.h"
#include "builtIn.h"
#include "Operat.h"
#include "condHandle.h"
#include "getALLvar.h"

// define
#define SYN_ERR ("is not a syntax")
#define EMPTY_STR ("nothing after")

// function
/* initialize the memories structures. Needed */
void initMem();

/* free the variable structure */
int freeVar(t_var *var);

/* free the stack structure */
int freeStack(t_stack *stack);

/* free the entire memorie */
void freeMem();

/* add a variable from C of type int */
void addInt(int *nb, char *name);

/* add a variable from C of type char */
void addStr(char *str, char *name);

/* return the var from chaussette exec */
int *getInt(char *name);

/* read the lead file */
/* on NULL, file = ./leadfile */
void readLeadFile(char *file);

/* execute the code given as parameters. Can return NULL on unfind int */
int chaussette(char *code);

void showMem(t_var *var);

#endif
