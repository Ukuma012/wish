#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

char *get(char *, int);
int getcmd(char *, int);

char *get(char *buf, int max) {
  int c, i;
  for(i = 0; i+1 < max; ) {
    c = fgetc(stdin);
    if(c == '\n')
      break;
    if(c < 0) 
      break;
    buf[i++] = c;
  }
  buf[i] = '\0';
  return buf;
}

int getcmd(char *buf, int nbuf) {
  // @TODO 今自分がどこにいるのか表示
  printf("%s", "wish> ");
  get(buf, nbuf);
  if(buf[0] == 0)
    return -1;
  return 0;
}

int main(int argc, char *argv[]) {
  char buf[BUFSIZE];
  while(getcmd(buf, sizeof(buf)) >= 0) {
    if(buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'i' && buf[3] == 't') {
      exit(0);
    }
    for(int j = 0; j < BUFSIZE; j++) {
      if(buf[j] == '\0') 
        break;
      printf("%c", buf[j]);
    }
    printf("\n");
  }
  return 0;
}
