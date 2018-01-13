#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libmy.h"
#include "lipsite.h"
#include "Chaussette.h"

int		main (int ac, char **av)
{
  t_item *item;

  initMem();
  if (av[1] == NULL)
  {
    my_puterror("Need a file with a main\n");
    my_puterror("press enter to exit\n");
    free(gnl(0));
    return (FAILURE);
  }
  setFileLink(av[1]);
  setItemInfo("name", "main");
  readLeadFile(NULL);
  item = createItem();
  if ((item = findItem(item)) == NULL)
  {
    my_puterror("Need a main function\n");
    my_puterror("press enter to exit\n");
    free(gnl(0));
    return (FAILURE);
  }
  chaussette(InItem(item, "function"));
  freeMem();
  freeInfo();
  freeItem(item);
  my_putstr("\npress enter to exit\n");
  free(gnl(0));
  return (SUCCESS);
}
