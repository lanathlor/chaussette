/*
** my_getstr.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:35:58 2016 valetin vivier
** Last update Sun Jul 10 15:51:17 2016 valetin vivier
*/

#include <stdlib.h>
#include "libmy.h"

int	power(int nb, int power)
{
  int	i;

  i = ZERO;
  if (power == ZERO)
    return (ONE);
  while (i < power - ONE)
    {
      nb = nb * nb;
      if (nb < 0)
	return (FAILURE);
      i++;
    }
  return (nb);
}

int      my_intlen(int nb)
{
  int	count;

  count = ONE;
  while (nb >= DECIMAL)
    {
      nb = nb / DECIMAL;
      count++;
    }
  return (count);
}

char	*my_getstr(int nb)
{
  int   i;
  char  *nb_str;
  int   cp;

  i = ZERO;
  cp = ONE;
  if (nb == ZERO)
    return (ZERO_ST);
  if (nb <= NEG_ONE)
    return (NULL);
  if ((nb_str = malloc(sizeof(char) * my_intlen(nb) + ONE)) == NULL)
    my_perror(M_FAIL);
  nb_str[ZERO] = ZERO;
  while (nb >= cp && i != my_intlen(nb))
    {
      nb_str[i] = ((nb / cp) % DECIMAL) + ZERO_C;
      if (nb_str[i] < ZERO_C || nb_str[i] > NINE_C)
	return (NULL);
      cp = cp * DECIMAL;
      i++;
    }
  nb_str[i] = ZERO;
  if ((nb_str = my_revstr(nb_str, SUCCESS)) == NULL)
    return (NULL);
  return (nb_str);
}
