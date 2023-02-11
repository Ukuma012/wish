#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  while(1) {
    printf("%s", "wish> ");
    if((linelen = getline(&line, &linecap, stdin)) > 0) {
      line[linelen -1] = '\0';
      if(strcmp(line, "exit") == 0) {
        exit(0);
      }
      // ここでparse

      char *args[10];
      char *string;
      int i = 0;
      while((string = strsep(&line, " ")) != NULL) {
        args[i] = string;
        i++;
      }
      args[i] = "NULL";
      for(int j = 0; j < i+1; j++) {
        printf("%s\n", args[j]);
      }
    }
  }
  return 0;
}

