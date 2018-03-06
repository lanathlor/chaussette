#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libmy.h"
#include "lipsite.h"
#include "Chaussette.h"

char  *gnlItem(int fd)
{
  char    *str;
  char    buff;

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

void  dump(void * mem)
{
  char *str = mem;
  int i;
  
  i = 0;
  while (str[i]){
    my_putnbrfd(str[i], 3);
    my_putstrfd(" ", 3);
    i++;
  }
}

void dumpAll(void)
{
  char *str;
  int i;
  int fd;

  i = 0;
  fd = 0;
  while (parseer.include[i]){
    fd = open(parseer.include[i], O_RDWR);
    while ((str = gnlItem(fd))){
      dump(str);
      my_putstrfd("\n", 3);
      free(str);
    }
    i++;
  }
}

int		main (int ac, char **av)
{
  int fd;

  ac++;
  if (av[1] == NULL)
  {
    my_puterror("Need a leadfile with a .cht extension");
    my_puterror("press enter to exit\n");
    free(gnl(0));
    return (FAILURE);
  }
  if (av[2] == NULL)
  {
    my_puterror("Need a leadfile with a .cht extension");
    my_puterror("press enter to exit\n");
    free(gnl(0));
    return (FAILURE);
  }
  fd = open(av[2], O_RDWR | O_CREAT);
  fd++;
  readLeadFile(av[1]);
  dumpAll();
  freeInfo();
  close(fd);
  system("gcc /usr/include/chaussette/main.c -I/usr/include/chaussette/lib/my -I/usr/include/chaussette -lchaussette -o test");
  return (SUCCESS);
}
