#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// first: 'ls' with no arguments

int main (int argc, char *argv[]) {
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while(1) {
    printf("wish> ");
    if((linelen = getline(&line, &linecap, stdin)) > 0) {
    fwrite(line, linelen, 1, stdout);
    }
    }
  return 0;
}
