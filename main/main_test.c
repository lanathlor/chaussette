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
  t_codex *codex;
  char *code;
  int nb;
  int i;
  char *str;

  nb = 2;
  i = 3;
  str = my_strcpy(str, "hello world", FAILURE);
  initMem();
  setFileLink("./chaussette_file/testlips.LPS");
  setItemInfo("name", "main");
  readLeadFile("chaussette_file/leadfile.cht");
  // codex = initCodex("caster target", "lanath", "try");
  // codex = addInCodex(codex, "target", "test");
  addInt(&nb, "nb");
  addInt(&i, "i");
  addStr(str, "str");
  item = createItem();
  item = findItem(item);
  //promptItem(item);
  //talkative(item, codex);
  code = InItem(item, "function");
  printf("ret = %d\n", chaussette(code));
  showAllMem();
  freeMem();
  printf("str = %s\n", str);
  //freeCodex(codex);
  freeInfo();
  freeItem(item);
  free(str);
  my_putstr("press enter to exit\n");
  gnl(0);
  return (0);
}
