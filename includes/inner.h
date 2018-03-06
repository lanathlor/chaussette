#ifndef INNER_H
# define INNER_H_

// define
# define NB_ELEM (20)

// structure
typedef struct s_item
{
  char	*element;
  char	*value;
}	       t_item;

typedef t_item* p_item;

typedef struct s_info
{
  char	*item_elem;
  char	*item_ValueOfElem;
  char	*file_path;
  int	fd;
}	       t_info;

typedef struct s_codex
{
  char	*type;
  char	*name;
}	       t_codex;

// globals
extern t_info	item_info;

// function
/* lipstie.c */
char	*my_reallocItem(char *str, char buff);

#endif