#ifndef USABLE_H_
# define USABLE_H_

//#include "lipsite.h"

# define NB_VAR (4)
# define NB_BOOL (3)
# define NB_INTER (3)
# define NB_OP (12)
# define NB_TYPE (3)

// stuctures

typedef struct s_func
{
  char *name;
  int (*fctn)(char **arg);
}				t_func;

typedef struct s_parseer
{
  char **include;
  t_func *function;
  int line;
  int words;
  int check;
  int cond;
  int string;
  int verbose;
//  t_item *loadded;
}			t_parseer;

typedef enum s_type
{
  _char,
  _int,
  _string,
  _null
}             t_type;

typedef struct s_var
{
  t_type type;
  void	*value;
  char	*name;

}				t_var;

typedef struct  s_ptr
{
  char          *str;
  int   (*fctn)(char **split, char **splitCommand);
  int     *(*var)(char *name);
  int     (*ptr)(char **split, char **words);
  int     (*op)(int var_left, int var_right);
  t_type  (*type)(char *name);
  t_var   *(*struc)(char *name);
}               t_ptr;

typedef struct s_stack
{
	char *instruct;
	t_var *var;
}				t_stack;

typedef struct s_mem
{
	t_var *var_fromC;
	t_stack *stack;
	t_var *var_toC;
	t_var *var_local;
  t_var *var_stack;
	int tmp;
}				t_mem;

// function
char	*gnlParseer(int fd);
char  **strtabParseer(const char *str, char delim);
void perrorPars(char **word, char *errorType);
int memLen(t_var *var);
int memCopy(t_var *new, t_var *var);
t_var *memRealloc(t_var *var);
int searchVar(t_var *var, char *name);
void testNULL(char **words);
t_var *memAdd(t_var *var, t_var add);
void initSyntax();
int parsing(char **split);

// global
extern t_parseer parseer; //parseer.c
extern t_mem mem; //usable.c
extern t_ptr varSyn[NB_VAR]; //parseer.c
extern t_ptr boolean_op[NB_BOOL]; //parseer.c
extern t_ptr interrupt[NB_INTER]; //parseer.c
extern t_ptr ptr[NB_OP]; //parseer.c

#endif
