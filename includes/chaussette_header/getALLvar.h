#ifndef GETALLVAR_H_
#define GETALLVAR_H_

t_var *findFromC(t_var *var, char *name);
t_var *findToC(t_var *var, char *name);
t_var *findLocal(t_var *var, char *name);

#endif