#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

// testcommand\0

int main(int argc, char *argv[]) {
  char buf[BUFSIZE];
  int c;
  int i;
  for(i = 0; i+1 < BUFSIZE; ){
    c = fgetc(stdin);
    if(c == '\n')
      break;
    if(c < 0) {
      fprintf(stderr, "fgets failed\n");
      exit(1);
    }
    buf[i++] = c;
  }
  buf[i] = '\0';
  for(int j = 0; j < i+1; j++) {
    printf("%c\n", buf[j]);
  }
  return 0;
 }
