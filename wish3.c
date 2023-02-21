#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// @TODO access system call
// @TODO redirection
// 処理を関数にまとめる

int main (int argc, char *argv[]) {
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  while(1) {
    char *args[10];
    char *string;
    int i = 0;
    printf("%s", "wish> ");
    if((linelen = getline(&line, &linecap, stdin)) > 0) {
      // 末尾の改行を終端に変更
      char *p;
      p = strchr(line, '\n');
      if(p != NULL) {
        *p = '\0';
      }

      while((string = strsep(&line, " ")) != NULL) {
        if(*string == '\0') {
          continue;
        }
        args[i] = string;
        i++;
      }
      args[i] = NULL;

      if(strcmp(args[0], "exit") == 0) {
        exit(0);
      }

      int rc = fork();
      if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
      }else if(rc == 0) {
        if((execv(args[0], args)) < 0) {
          printf("%s\n", args[0]);
          fprintf(stderr, "execv failed\n");
          exit(1);
        }
        exit(0);
      } else {
        wait(NULL);
      }
    }
  }
  return 0;
}
