/*
** my_strcpy.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:38:03 2016 valetin vivier
** Last update Sun Jul 10 14:32:01 2016 valetin vivier
*/

#include <stdlib.h>
#include "libmy.h"

char	*my_strcpy(char *dest, char *src, int free_ck)
{
  int	i;

  i = NEG_ONE;
  dest = NULL;
  if (src == NULL)
    return (NULL);
  if ((dest = malloc(sizeof(char) * my_strlen(src) + ONE)) == NULL)
    my_perror(M_FAIL);
  while (src[++i])
    dest[i] = src[i];
  dest[i] = ZERO;
  if (free_ck == SUCCESS)
    free(src);
  return (dest);
}
