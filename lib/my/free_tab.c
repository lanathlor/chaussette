/*
** free_tab.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:34:52 2016 valetin vivier
** Last update Sun Jul 10 14:17:18 2016 valetin vivier
*/

#include <stdlib.h>
#include "libmy.h"

void	free_error(char *error, char *str, char *str2)
{
  if (str != NULL)
    free(str);
  if (str2 != NULL)
    free(str2);
  my_perror(error);
}

void	free_tab(char **tab)
{
  int	inc;

  inc = ZERO;
  while (tab[inc])
    free(tab[inc++]);
  free(tab);
}
