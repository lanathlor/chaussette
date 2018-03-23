#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libmy.h>
#include <string.h>
#include <lipsite.h>
#include <Chaussette.h>

static void usage(void)
{
  printf("USAGE:\n");
  printf("\tchaussette file [option]\n");
  printf("OPTION\n");
  printf("\t-v [x], --vebose [x]\tset the verbosity level of the interpreter\n");
  printf("\t--no-load\t\tdisable the preload of functions, save ram, lose time\n");
}

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
    if ((item = findItem(item)) != NULL){
      freeInfo();
      return (item);
    }
    freeItem(item);
    inc++;
  }
  my_perror("There is no main function defined\n");
  return (NULL);
}

static char *get_arg(char *arg)
{
  int i;

  i = 0;
  if (arg == NULL){
    usage();
    exit(-1);
  }
  while (arg[i]){
    if (arg[i] > '9' || arg[i] < '0'){
      usage();
      exit(-1);
    }
    i++;
  }
  return (arg);
}

static char *read_arg(char **av)
{
  char *file;
  int i;

  i = 0;
  while (av[i]){
    if (strcmp(av[i], "-v") == 0 || strcmp(av[i], "--verbose") == 0)
      parseer.verbose = atoi(get_arg(av[i + 1]));
    if (strcmp(av[i], "--no-load") == 0)
      parseer.preload = 0;
    if (strstr(av[i], ".cht") != NULL)
      file = av[i];
    i++;
  }
  return (file);
}

int		main (int ac, char **av)
{
  t_item *item;
  char *file;

  ac++;
  initMem();
  parseer.preload = 1;
  file = read_arg(av);
  if (file == NULL) {
    usage();
    return (FAILURE);
  }
  readLeadFile(file);
  item = createItem();
  item = haveFunc(item);
  chaussette(InItem(item, "function"), "main");
  freeMem();
  freeInfo();
  freeItem(item);
  return (SUCCESS);
}
