/*
** my_strlen.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:38:23 2016 valetin vivier
** Last update Thu Jul  7 12:46:57 2016 valetin vivier
*/

#include <stdlib.h>
#include "libmy.h"

int	my_strlen(const char *str)
{
  int	i;

  i = ZERO;
  if (str == NULL)
    return (ZERO);
  while (str[i])
    i++;
  return (i);
}

int	my_tablen(const char **tab)
{
  int	i;

  i = ZERO;
  if (tab == NULL)
    return (i);
  while (tab[i])
    i++;
  return (i);
}
