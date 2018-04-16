/*
** my_strcmp.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:37:51 2016 valetin vivier
** Last update Sat Jun 25 14:37:52 2016 valetin vivier
*/

#include <stdlib.h>
#include "libmy.h"

int	check_in_tab(char **tab, char *str)
{
  int	i;

  i = ZERO;
  if (tab == NULL)
    return (FAILURE);
  while (tab[i] != NULL)
    {
      if (my_strcmp(tab[i], str) == SUCCESS)
	return (SUCCESS);
      i++;
    }
  if (!tab[i])
    return (FAILURE);
  return (SUCCESS);
}

int	my_strcmp(const char *str1, const char *str2)
{
  int	i;

  i = ZERO;
  if (str1 == NULL || str2 == NULL)
    return (FAILURE);
  while (str1[i] && str2[i] && str1[i] == str2[i])
    i++;
  if (!str1[i] && !str2[i])
    return (SUCCESS);
  return (FAILURE);
}
