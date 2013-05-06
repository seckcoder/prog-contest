#include <stdio.h>


int main(int argc, const char *argv[]) {
  int t;
  scanf("%d", &t);

  char buf[10000000];

  while (t--) {
    scanf("%s", buf);
    int rownum=-1,colnum=-1;
    sscanf(buf, "R%dC%d", &rownum, &colnum);
    if (rownum >= 1 && colnum >= 1) {

    }
  }
  return 0;
}
