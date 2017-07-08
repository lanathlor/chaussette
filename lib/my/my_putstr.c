/*
** my_putstr.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:37:07 2016 valetin vivier
** Last update Sat Jul  9 23:13:15 2016 valetin vivier
*/

#include <unistd.h>
#include <stdio.h>
#include "libmy.h"

void	my_putchar(char c)
{
  write(ONE, &c, ONE);
}

int	my_putcharfd(char c, int fd)
{
  return (write(fd, &c, ONE));
}

void    my_putstr(const char *str)
{
  write (ONE, str, my_strlen(str));
}


int	my_putstrfd(const char *str, int fd)
{
  return (write(fd, str, my_strlen(str)));
}

int	my_puttab(const char **tab)
{
  int	i;

  i = ZERO;
  if (tab == NULL)
    my_perror(R_FAIL);
  while (tab[i])
    {
      my_putstr(tab[i]);
      my_putchar(B_N);
      i++;
    }
  return (SUCCESS);
}
