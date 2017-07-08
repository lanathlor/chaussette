/*
** tab_malloc.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:39:12 2016 valetin vivier
** Last update Sat Jun 25 14:39:13 2016 valetin vivier
*/

#include <stdlib.h>
#include "libmy.h"

char	**reallocTab(char **tab, char *str)
{
	char **newTab;
	int inc;

	if ((newTab = malloc(sizeof(char *) * (my_tablen((const char **)tab) + 2))) == NULL)
		my_perror(M_FAIL);
	inc = 0;
	while (tab[inc])
	{
		newTab[inc] = my_strcpy(newTab[inc], tab[inc], FAILURE);
		inc++;
	}
	newTab[inc] = my_strcpy(newTab[inc], str, FAILURE);
	newTab[inc + 1] = NULL;
	free(tab);
	tab = NULL;
	return (newTab);
}

char	**tab_malloc(int i)
{
  char	**tab;
  int	inc;

  inc = ZERO;
  if ((tab = malloc(sizeof(char *) * i * DECIMAL)) == NULL)
    my_perror(M_FAIL);
  while (inc != i * DECIMAL)
    tab[inc++] = NULL;
  return (tab);
}
