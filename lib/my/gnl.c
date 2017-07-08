/*
** gnl.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:35:06 2016 valetin vivier
** Last update Sat Jun 25 14:35:07 2016 valetin vivier
*/

#include <unistd.h>
#include <stdlib.h>
#include "libmy.h"

char	*my_realloc(char *str, char buff)
{
  char	*tmp;
  int	i;

  if ((tmp = malloc(my_strlen(str) + TWO)) == NULL)
    my_perror(M_FAIL);
  i = ZERO;
  if (str != NULL)
    while (str[i] != '\0')
      {
	       tmp[i] = str[i];
	       i = i + ONE;
      }
    tmp[i] = buff;
    tmp[i + ONE] = '\0';
    free(str);
  return (tmp);
}

char	*gnl(int fd)
{
  char	*str;
  char	buff;

  buff = ZERO;
  str = NULL;
  while (read(fd, &buff, ONE) > ZERO && buff != B_N)
    str = my_realloc(str, buff);
  return (str);
}
