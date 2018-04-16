#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libmy.h"
#include "lipsite.h"
#include "Chaussette.h"

void reread(char *str)
{
  int i;
  int j;
  char *tmp;

  tmp = malloc(my_strlen(str));
  if (tmp == NULL)
    my_perror(M_FAIL);
  i = 0;
  j = 0;
  tmp[i] = 0;
  while (str[j]){
    if (str[j] != ' ')
      tmp[i] = (tmp[i] * 10) + (str[j] - '0');
    if (str[j] == ' '){
      i++;
      tmp[i] = 0;
    }
    j++;
  }
  my_putstr(tmp);
  my_putstr("\n");
}

int		main (int ac, char **av)
{
  int fd;
  char *str;

  ac++;
  if (av[1] == NULL)
  {
    my_puterror("Need a leadfile with a .cht extension");
    my_puterror("press enter to exit\n");
    free(gnl(0));
    return (FAILURE);
  }
 if ((fd = open(av[1], O_RDWR)) == FAILURE){
    my_puterror(O_FAIL);
    my_puterror("press enter to exit\n");
    free(gnl(0));
    return (FAILURE);
 }
  while ((str = gnl(fd))){
    reread(str);
    free(str);
  }
  close(fd);
  return (SUCCESS);
}
