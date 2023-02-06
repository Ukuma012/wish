#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while(1) {
    printf("wish> ");
    if((linelen = getline(&line, &linecap, stdin)) > 0) {
      if(strcmp(line, "exit\n") == 0) {
        exit(0);
      } else {
        fwrite(line, linelen, 1, stdout);
        line = NULL;
      }
    }
  }
  return 0;
}
