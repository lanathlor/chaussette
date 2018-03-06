/*
** Lipsite.c for Lipsite in /home/vivier_v/jeux/Lipsite
** 
** Made by valetin vivier
** Login   <vivier_v@epitech.net>
** 
** Started on  Thu Sep  8 13:30:30 2016 valetin vivier
** Last update Thu Sep  8 13:36:52 2016 valetin vivier
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "libmy.h"
#include "lipsite.h"

t_info item_info;


static void openWithPath(void)
{
  if (item_info.fd != 0)
  {
    close(item_info.fd);
    if ((item_info.fd = open(item_info.file_path, O_RDWR)) == -1)
      {
        my_puterror("(Lipsite) ERROR : File needed is not valid : ");
        my_puterror(item_info.file_path);
        my_perror(".\n");
      }
  }
}

static int generatMagicNb(void)
{
  int      nb;
  int      i;
  int      stop;
  char     c;

  nb = 0;
  i = 0;
  stop = 0;
  c = 0;
  openWithPath();
  while (read(item_info.fd, &c, 1) && stop != 3)
  {
    if (c == '#' || c == 'N' || c == 'b')
      stop++;
    else
      stop = 0;
    nb += c;
    i++;
  }
  nb *= i;
  return (nb);
}

static void positionOnMagicNb(void)
{
  int       i;
  int       stop;
  char      c;
  
  openWithPath();
  i = 0;
  stop = 0;
  while (read(item_info.fd, &c, 1) && stop != 3)
  {
    if (c == '#' || c == 'N' || c == 'b')
      stop++;
    else
      stop = 0;
    i++;
  }
  if (stop == 3)
    i -= 4;
  openWithPath();
  while (i)
  {
    read(item_info.fd, &c, 1);
    i--;
  }
}

static void copyStruct(t_item *item, t_item *newItem)
{
  int i;

  i = 0;
  while (item[i].value && item[i].element)
  {
    newItem[i].element = my_strcpy(newItem[i].element, item[i].element, FAILURE);
    newItem[i].value = my_strcpy(newItem[i].value, item[i].value, FAILURE);
    i++;
  }
  newItem[i].element = NULL;
  newItem[i].value = NULL;
  newItem[i + 1].element = NULL;
  newItem[i + 1].value = NULL;
}

static int lenOfStruct(t_item *item)
{
  int i;

  i = 0;
  while (item[i].element && item[i].value)
    i++;
  return (i);
}

static t_item *reallocStructItem(t_item *item)
{
  t_item *newItem;

  if ((newItem = malloc(sizeof(t_item) * (lenOfStruct(item) + 2))) == NULL)
    my_perror(M_FAIL);
  copyStruct(item, newItem);
  freeItem(item);
  return(newItem);
}

char	*my_reallocItem(char *str, char buff)
{
  char	*tmp;
  int	i;

  if ((tmp = malloc(my_strlen(str) + TWO)) == NULL)
    my_perror(M_FAIL);
  i = ZERO;
  if (str != NULL)
  {
    while (str[i] != '\0')
      {
      	 tmp[i] = str[i];
	       i = i + ONE;
      }
    }
    tmp[i] = buff;
    tmp[i + ONE] = '\0';
    free(str);
    return (tmp);
}

static char	*gnlItem(int fd)
{
  char		*str;
  char		buff;

  buff = ZERO;
  str = NULL;
  while (read(fd, &buff, ONE) > ZERO && buff != '<')
    ;
  while (read(fd, &buff, ONE) > ZERO && buff != '>')
    {
      if (buff == '"')
      {
        str = my_reallocItem(str, buff);
        while (read(fd, &buff, ONE) > ZERO && buff != '"')
          {
            if (buff != '\n' && buff != '\t')
              str = my_reallocItem(str, buff);
          }
        str = my_reallocItem(str, '"');
      }
      else if (buff != '\n')
      	str = my_reallocItem(str, buff);
    }
  if (my_strlen(str) > ZERO)
    str = my_reallocItem(str, '>');
  return (str);
}

static int	itIsInThis(char **tmp, t_info item_info)
{
  int		i;

  i = ZERO;
  while (tmp[i])
    {
      if (my_strcmp(tmp[i], item_info.item_elem) == SUCCESS && 
	  my_strcmp(tmp[i + 1], item_info.item_ValueOfElem) == SUCCESS)
	return (SUCCESS);
      i++;
    }
  return (FAILURE);
}

static int	getStruct(t_item *item, char *info, int elem, int i)
{
  int		inc;

  if ((item[elem].value = malloc(my_strlen(info))) == NULL)
    my_puterror(M_FAIL);
  if ((item[elem].element = malloc(100)) == NULL)
    my_puterror(M_FAIL);
  inc = ZERO;
  while (info[i] != '=')
    {
      if (info[i] == '"')
	{
	  printf("(Lipsite) ERROR : Wrong format after : %c | %c (%d).\n", 
		 info[i - 1], info[i], i);
	  exit(FAILURE);
	}
      item[elem].element[inc++] = info[i++];
    }
  item[elem].element[inc] = ZERO;
  i += 2;
  inc = ZERO;
  while (info[i] != '"')
    {
      item[elem].value[inc++] = info[i++];
    }
  item[elem].value[inc] = '\0';
  while(info[i] == ' ' || info[i] == '"' || info[i] == ',')
    i++;
  return (i);
}

static char	*findInDoc(t_info item_info)
{
  char		*tmp;
  char		**tab_res;

  tmp = NULL;
  while ((tmp = gnlItem(item_info.fd)) != NULL)
    {
      tab_res = my_strtab(tmp);
      if (itIsInThis(tab_res, item_info) == SUCCESS)
  {
    free_tab(tab_res);
    break;
  }
      else
  {
    free(tmp);
    tmp = NULL;
  }
      free_tab(tab_res);
    }
  return (tmp);
}

/* ////EXTERIOR FUNCTION ////////// */

t_item *createItem()
{
  t_item *item;

  if ((item = malloc(sizeof(t_item) * 1)) == NULL)
    my_perror(M_FAIL);
  item[0].element = NULL;
  item[0].value = NULL;
  return (item);
}

void	setFileLink(char *link)
{
  if (my_strlen(item_info.file_path) > 0)
    free(item_info.file_path);
  if (item_info.fd != 0)
    close(item_info.fd);
  if (link == NULL)
    my_perror("(Lipsite) ERROR : No link given.\n");
  if ((item_info.fd = open(link, O_RDWR)) == -1)
    {
      my_puterror("(Lipsite) ERROR : File needed is not valid : ");
      my_puterror(link);
      my_perror(".\n");
    }
  item_info.file_path = my_strcpy(item_info.file_path, link, FAILURE);
}

void	setItemInfo(char *elem, char *value)
{
  if (item_info.fd != 0)
  {
    close(item_info.fd);
    if ((item_info.fd = open(item_info.file_path, O_RDWR)) == -1)
      {
        my_puterror("(Lipsite) ERROR : File needed is not valid : ");
        my_puterror(item_info.file_path);
        my_perror(".\n");
      }
  }
  if (elem == NULL || value == NULL)
    my_perror("(Lipsite) ERROR : the element or is value wasnt given.\n");
  if (my_strlen(item_info.item_elem) > 0)
    free (item_info.item_elem);
  if (my_strlen(item_info.item_ValueOfElem) > 0)
    free(item_info.item_ValueOfElem);
  item_info.item_elem = my_strcpy(item_info.item_elem, elem, FAILURE);
  item_info.item_ValueOfElem = my_strcpy(item_info.item_ValueOfElem, value, FAILURE);
}

void	freeInfo(void)
{
  if (my_strlen(item_info.item_elem) > 0)
    {
      free(item_info.item_elem);
      item_info.item_elem = NULL;
    }
  if (my_strlen(item_info.item_ValueOfElem) > 0)
    {
      free(item_info.item_ValueOfElem);
      item_info.item_ValueOfElem = NULL;
    }
  if (my_strlen(item_info.file_path) > 0)
    {
      free(item_info.file_path);
      item_info.file_path = NULL;
    }
  if (item_info.fd != 0)
  {
    close (item_info.fd);
    item_info.fd = 0;
  }
}

int freeItem(t_item *item)
{
  int	i;

  i = 0;
  if (item == NULL)
    return (FAILURE);
  while (item[i].element || item[i].value)
    {
      if (my_strlen(item[i].element) > 0)
	{
	  free (item[i].element);
	  item[i].element = NULL;
	}
      if (my_strlen(item[i].value) > ZERO)
	{
	  free(item[i].value);
	  item[i].value = NULL;
	}
      i++;
    }
//    free(item);
  return (SUCCESS);
}

char *InItem(t_item *item, char *tag)
{
  int i;

  i = 0;
  if (item == NULL)
    return (NULL);
  while (item[i].element != NULL && item[i].value != NULL)
    {
      if (my_strcmp(item[i].element, tag) == SUCCESS)
        return (item[i].value);
      i++;
    }
  return (NULL);
}

void promptItem(t_item *item)
{
  int i;

  i = 0;
  if (item == NULL)
    printf("item is NULL\n");
  if (item != NULL)
  {
    while (item[i].element && item[i].value)
    {
      printf("%s | %s\n", item[i].element, item[i].value);
      i++;
    }
  }
}

t_item  *getInfo(char *info)
{
  int   i;
  int   elem;
  t_item *item;

  i = ZERO;
  elem = ZERO;
  if (info == NULL)
    return (NULL);
  item = createItem();
  while (info[i] != '>')
    {
      item = reallocStructItem(item);
      i = getStruct(item, info, elem, i);
      elem++;
    }
  item[elem].element = NULL;
  item[elem].value = NULL;
  return (item);
}

t_item  *findItem(t_item *item)
{
  char  *info;

  if ((info = findInDoc(item_info)) == NULL)
    return (NULL);
  item = getInfo(info);
  free(info);
  return (item);
}

t_item     *duplicateFromRecipe(t_item *recipe, char **data)
{
  t_item  *item;
  int     i;
  int     valid;

  item = createItem();
  i = 0;
  valid = 1;
  while (recipe[i].element != NULL)
  {
    item = reallocStructItem(item);
    item[i].element = my_strcpy(item[i].element, recipe[i].element, FAILURE);
    if (data[i] && valid)
      item[i].value = my_strcpy(item[i].value, data[i], FAILURE);
    else
    {
      item[i].value = my_strcpy(item[i].value, " ", FAILURE);
      valid = 0;
    }
    i++;
  }
  return (item);
}

int   appendItem(t_item *item)
{
  int i;

  i = 0;
  positionOnMagicNb();
  my_putstrfd("\n<", item_info.fd);
  while (item[i].element)
  {
    my_putstrfd(item[i].element, item_info.fd);
    my_putstrfd("=\"", item_info.fd);
    if (my_strcmp(item[i].value, " ") == FAILURE)
      my_putstrfd(item[i].value, item_info.fd);
    my_putstrfd("\"", item_info.fd);
    if (item[i + 1].element)
      my_putstrfd(", ", item_info.fd);
    i++;
  }
  my_putstrfd(">", item_info.fd);
  return (SUCCESS);
}

int     appendMagicNb(void)
{
  int   nb;

  nb = 0;
  nb = generatMagicNb();
  positionOnMagicNb();
  my_putstrfd("\n#Nb", item_info.fd);
  my_putnbrfd(nb, item_info.fd);
  return (nb);
}

int     verifyMagicNb(void)
{
  char *str;
  char *tmp;

  str = NULL;
  positionOnMagicNb();
  str = gnl(item_info.fd);
  str = gnl(item_info.fd);
  tmp = my_hashstr(str, 3, my_strlen(str), SUCCESS);
  if (generatMagicNb() == my_getnbr(tmp, SUCCESS))
    return (SUCCESS);
  return (FAILURE);
}

static p_item copyItem(t_item *item)
{
  t_item *newItem;
  int i;

  i = 0;
  if (item == NULL)
    return (NULL);  
  newItem = createItem();
  while (item[i].element && item[i].value){
    newItem = reallocStructItem(newItem);
    newItem[i].element = my_strcpy(newItem[i].element, item[i].element, FAILURE);
    newItem[i].value = my_strcpy(newItem[i].value, item[i].value, FAILURE);
    i++;
  }
  newItem[i].element = NULL;
  newItem[i].value = NULL;
  return (newItem);
}

static  int getLenOfItem(p_item *item)
{
  int i;

  i = 0;
  if (item == NULL)
    return (-1);
  while (item[i])
    i++;
  return (i);
}

p_item *reallocItem(p_item *item, p_item add)
{
  p_item *newItem;
  int i;

  i = 0;
  if ((newItem = malloc(sizeof(p_item) * (getLenOfItem(item) + 2))) == NULL)
    my_perror(M_FAIL);
  while (item && item[i]){
    newItem[i] = copyItem(item[i]);
    i++;
  }
  newItem[i] = copyItem(add);
  newItem[i + 1] = NULL;
  return(newItem);
}

p_item readItem(void)
{
  p_item item;
  char *str;

  item = createItem();
  str = gnlItem(item_info.fd);
  item = getInfo(str);
  return (item);
}