/*
** my_strcat.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:37:37 2016 valetin vivier
** Last update Sun Jul 10 14:33:13 2016 valetin vivier
*/

#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"

char	*my_strcat(char *dest, char *src, int free_ck)
{
  int	i;

  i = ZERO;
  if (dest == NULL)
    {
      if ((dest = malloc(sizeof(char) * ONE)) == NULL)
	my_perror(M_FAIL);
      dest[ZERO] = ZERO;
    }
  if (src == NULL)
    return (dest);
  while (src[i])
    {
      if ((dest = my_realloc(dest, src[i])) == NULL)
	my_perror(M_FAIL);
      i++;
    }
  if (free_ck == SUCCESS)
    free(src);
  return (dest);
}

char *my_strdup(char *src)
{
  char *ret;
  int   i;

  i = 0;
  if (src == NULL)
    return (NULL);
  ret = malloc(sizeof(char) * 1);
  ret[0] = 0;
  if (ret == NULL)
    my_perror(M_FAIL);
  while (src[i]){
    ret = my_realloc(ret, src[i]);
    if (ret == NULL)
      my_perror(M_FAIL);
    i++;
  }
  return (ret);
}