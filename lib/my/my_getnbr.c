/*
** my_getnbr.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:35:43 2016 valetin vivier
** Last update Thu Jul 14 16:19:13 2016 valetin vivier
*/

#include <stdlib.h>
#include "libmy.h"

int	my_getnbr(char *str, int free_ck)
{
  int	nb;
  int	i;

  nb = ZERO;
  i = ZERO;
  if (str == NULL)
    return (FAILURE);
  if (str[i] == DASH)
    i += ONE;
  while (str[i])
    {
      if ((nb > ((MAX_INT - (str[i] - ZERO_C)) / DECIMAL)) ||
	  str[i] < ZERO_C || str[i] > NINE_C)
	{
	  if (free_ck == SUCCESS)
	    free(str);
	  return (ZERO);
	}
      nb = nb * DECIMAL + str[i] - ZERO_C;
      i++;
    }
  if (str[ZERO] == DASH)
    nb = nb * NEG_ONE;
  if (free_ck == SUCCESS)
    free(str);
  return (nb);
}
