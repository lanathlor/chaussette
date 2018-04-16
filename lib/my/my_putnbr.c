/*
** my_putnbr.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:36:52 2016 valetin vivier
** Last update Wed Jul 13 18:23:34 2016 valetin vivier
*/

#include <unistd.h>
#include "libmy.h"

void	my_putnbr(int nb)
{
  int i;

  i = ONE;
  if (nb < ZERO)
    {
      my_putchar('-');
      nb *= NEG_ONE;
    }
  while (nb / i >= DECIMAL)
    i = i * DECIMAL;
  while (i != ONE)
    {
      my_putchar(nb / i + ZERO_C);
      nb = nb % i;
      i = i / DECIMAL;
    }
  my_putchar(nb % DECIMAL + ZERO_C);
}

void    my_putnbrfd(int nb, int fd)
{
  int i;

  i = ONE;
  if (nb < 0)
    {
      my_putcharfd('-', fd);
      nb *= NEG_ONE;
    }
  while (nb / i >= DECIMAL)
    i = i * DECIMAL;
  while (i != ONE)
    {
      my_putcharfd(nb / i + ZERO_C, fd);
      nb = nb % i;
      i = i / DECIMAL;
    }
  my_putcharfd(nb % DECIMAL + ZERO_C, fd);
}
