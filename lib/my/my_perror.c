/*
** my_perror.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:36:23 2016 valetin vivier
** Last update Sat Jun 25 14:36:24 2016 valetin vivier
*/

#include <unistd.h>
#include <stdlib.h>
#include "libmy.h"

int	my_puterror(const char *str)
{
  write(TWO, str, my_strlen(str));
  return (FAILURE);
}

void	my_perror(const char *str)
{
  write(TWO, str, my_strlen(str));
  exit(ERROR);
}
