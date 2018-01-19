#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libmy.h"
#include "lipsite.h"
#include "Chaussette.h"

static t_item *haveFunc(t_item *item)
{
  int inc;

  inc = 0;
  setItemInfo("name", "main");
  if (parseer.include == NULL || parseer.include[0] == NULL)
    my_perror("There is no function file loaded");
  while (parseer.include[inc])
  {
    item = createItem();
    setFileLink(parseer.include[inc]);
    if ((item = findItem(item)) != NULL)
      return (item);
    freeItem(item);
    inc++;
  }
  my_perror("There is no main function defined\n");
  return (NULL);
}

int		main (int ac, char **av)
{
  t_item *item;

  ac++;
  initMem();
  if (av[1] == NULL)
  {
    my_puterror("Need a leadfile with a .cht extension");
    my_puterror("press enter to exit\n");
    free(gnl(0));
    return (FAILURE);
  }
  readLeadFile(av[1]);
  item = createItem();
  item = haveFunc(item);
  chaussette(InItem(item, "function"));
  freeMem();
  freeInfo();
  freeItem(item);
  my_putstr("\npress enter to exit\n");
  free(gnl(0));
  return (SUCCESS);
}
