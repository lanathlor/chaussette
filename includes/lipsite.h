#ifndef LIPSITE_H_
# define LIPSITE_H_

#include "inner.h"

/* readItem find and read info about the item set-uped with setItemInfo */
/* read as many item that it can, one by one */
/* return NULL when no item was found else the item is returned */
t_item	*findItem(t_item *item);

/* setFileLink open file given with the 'link' path in order be used */
void	setFileLink(char *link);

/* setItemInfo set the information needed for the search */
void	setItemInfo(char *elem, char *value);

/* free all the mem allocated used by t_info and close properly the file */
void	freeInfo(void);

/* free all the allocated mem needed by t_item */
/* return -1 (FAILURE) if item is already NULL */
int	freeItem (t_item *item);

/* Free the codex's infos */
void	freeCodex(t_codex *codex);

/* link types with respective name in string string (format is : initCodex("ex1 ex2", name1, name2)*/
t_codex	*initCodex(char *types, .../* char * */);

/* add an entry in the codex */
t_codex *addInCodex(t_codex *codex, char *type, char *name);

/* save the current codex, dont free space */
int 	keepCodex(t_codex *old_codex);

/* output the text of the item by remplacing the %type% by the name in the t_codex */
/* can return -1 on error, describe it on the standart output, dut exit */
int	talkative (t_item *item, t_codex *codex);

/* find the 'name' element in the item and return it, return NULL if nothing where found */
char *InItem (t_item *item, char *name);

/* output the item as "element | value" on standart output */
void promptItem(t_item *item);

/* inisialize item */
/* can return NULL */
t_item *createItem(void);

/* transform the info into an item */
t_item	*getInfo(char *info);

p_item *reallocItem(p_item *item, p_item add);

p_item readItem(void);

#endif