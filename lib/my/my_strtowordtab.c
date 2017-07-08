/*
** my_strtowordtab.c for libmy in /home/vivier_v/script
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Sat Jun 25 14:39:00 2016 valetin vivier
** Last update Sat Jun 25 14:39:01 2016 valetin vivier
*/

#include <stdlib.h>
#include "libmy.h"

static int	is_alpha(char c)
{
  if (c == ZERO)
    return (SUCCESS);
  if ((c >= A_C && c <= Z_C) || (c >= UA_C && c <= UZ_C)
      || (c >= ZERO_C && c <= NINE_C) || c == '"')
    return (SUCCESS);
  return (FAILURE);
}

static char	**my_strtowordtab(const char *str, char **word)
{
  int		i;
  int		s;

  i = ZERO;
  s = ZERO;
  while (str[s])
    {
      if (str[s] == '"')
      {
        s++;
        while (str[s] != '"')
         word[i] = my_realloc(word[i], str[s++]);
        s++;
      }
      else if (is_alpha(str[s]) == SUCCESS)
         word[i] = my_realloc(word[i], str[s++]);
      else
    	{
	      while (is_alpha(str[s++]) == FAILURE)
	       ;
	     s--;
	     if (my_strlen(word[i]) >= 1)
            i++;
	     }
    }
  word[i + ONE] = ZERO;
  return (word);
}

static char	**my_compressor(char **tab, int i)
{
  if (!tab[i + ONE])
    {
      tab[i] = NULL;
      return (tab);
    }
  i++;
  while (tab[i] && tab[i + ONE])
    {
      tab[i - ONE] = my_strcpy(tab[i - ONE], tab[i], FAILURE);
      i++;
    }
  tab[i - ONE] = NULL;
  return (tab);
}

char	**my_strtab(const char *str)
{
  int	i;
  char	**tab;

  i = ZERO;
  tab = NULL;
  tab = tab_malloc(my_strlen(str));
  tab = my_strtowordtab(str, tab);
  while (tab[i])
    {
      if (tab[i][ZERO] == ZERO)
	{
	  if ((tab = my_compressor(tab, i)) == NULL)
	    return (NULL);
	  i = ZERO;
	}
      else
	i++;
    }
  return (tab);
}
