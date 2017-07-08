/*
** my_hashstr.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:36:11 2016 valetin vivier
** Last update Sun Jul 10 14:34:20 2016 valetin vivier
*/

#include <unistd.h>
#include <stdlib.h>
#include "libmy.h"

char	*my_hashstr(char *str, int i, int j, int free_ck)
{
  int	inc;
  char	*dest;

  inc = ZERO;
  if (str == NULL)
    return (NULL);
  if ((dest = malloc(sizeof(char) * (my_strlen(str) + ONE))) == NULL)
    my_perror(M_FAIL);
  while (i < j && str[i])
    dest[inc++] = str[i++];
  dest[inc] = ZERO;
  if (free_ck == SUCCESS)
    free(str);
  return (dest);
}
