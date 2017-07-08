/*
** my_revstr.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:37:23 2016 valetin vivier
** Last update Sat Jun 25 14:37:24 2016 valetin vivier
*/

#include <stdlib.h>
#include "libmy.h"

char    *my_revstr(char *str, int free_ck)
{
  int   i;
  int   i2;
  char  *dest;

  i = ZERO;
  if (my_strlen(str) == ONE)
    return (str);
  i2 = my_strlen(str) - ONE;
  if ((dest = malloc(sizeof(char) * my_strlen(str) + ONE)) == NULL)
    return (NULL);
  while (i2 != NEG_ONE)
    {
      dest[i] = str[i2];
      i++;
      i2--;
    }
  dest[i] = ZERO;
  if (free_ck == SUCCESS)
    free(str);
  return (dest);
}
