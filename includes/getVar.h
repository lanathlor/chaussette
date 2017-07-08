#ifndef GETVAR_H_
#define GETVAR_H_

t_var *VtoC(char *var);
t_var *Vlocal(char *var);
t_var *VfromC(char *var);
t_var *getVar(char **words);
t_var *getVarFromPart(char **words);

#endif