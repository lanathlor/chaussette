/*
** my_putbase.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:36:37 2016 valetin vivier
** Last update Sat Jun 25 14:36:38 2016 valetin vivier
*/

#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"

void	my_putbase(int nb, char *base)
{
  if (nb < ZERO)
    {
      my_putchar('-');
      nb = nb * - 1;
      my_putbase(nb, base);
    }
  else if (nb < my_strlen(base))
    my_putchar(base[nb]);
  else
    {
      my_putbase(nb / my_strlen(base), base);
      my_putchar(base[nb % my_strlen(base)]);
    }
}

int	convert(int number, int base, int base_org)
{
  if (number == ZERO || base == base_org)
    return (number);
  return ((number % base) + base_org * convert(number / base, base, base_org));
}

char	*my_getnbrbase(char *nb, int base, int base_org, int free_ck)
{
  char	*str;

  str = my_getstr(convert(my_getnbr(nb, FAILURE), base, base_org));
  if (free_ck == SUCCESS)
    free(nb);
  return (str);
}
