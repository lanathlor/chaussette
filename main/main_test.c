#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libmy.h"
#include "lipsite.h"
#include "Chaussette.h"

void  dump(void * mem)
{
  char *str = mem;
  int i;
  
  i = 0;
  while (str[i]){
    my_putnbr(str[i]);
    i++;
  }
}

int		main (int ac, char **av)
{
  t_item *item;
//  t_codex *codex;
  char *code;
  int nb;
  int i;
  char *str;

  ac++;
  (void) av;
  nb = 2;
  i = 3;
  str = NULL;
  str = my_strcpy(str, "hello world", FAILURE);
  initMem();
  setFileLink("./chaussette_file/testlips.LPS");
  setItemInfo("name", "main");
  item = createItem();
  item = findItem(item);
  freeInfo();
  readLeadFile("./chaussette_file/leadfile.cht");
  // codex = initCodex("caster target", "lanath", "try");
  // codex = addInCodex(codex, "target", "test");
  addInt(&nb, "nb");
  addInt(&i, "i");
  addStr(str, "str");
  //promptItem(item);
  //talkative(item, codex);
  code = InItem(item, "function");
  printf("ret = %d\n", chaussette(code, "main"));
  printf("str = %s\n", str);
  freeMem();
  //freeCodex(codex);
  freeItem(item);
  free(str);
  return (0);
}
