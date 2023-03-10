#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  while(1) {
    printf("%s", "wish> ");
    if((linelen = getline(&line, &linecap, stdin)) > 0) {
      // 末尾の改行を終端に変更
      char *p;
      p = strchr(line, '\n');
      if(p != NULL) {
        *p = '\0';
      }
      if(strcmp(line, "exit") == 0) {
        exit(0);
      }
      int rc = fork();
      if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
      }else if(rc == 0) {
        char *args[3];
        char dst[20];
        char *string;
        int i = 0;
        while((string = strsep(&line, " ")) != NULL) {
          args[i] = string;
          i++;
        }
        args[i] = NULL;

        if(strcmp(args[0], "cd") == 0) {
          if(chdir(args[1]) < 0) {
            fprintf(stderr, "cd failed!\n");
            exit(1);
          }
          exit(0);
        }

        snprintf(dst, sizeof(dst), "/bin/%s", args[0]);
        if((access(dst, X_OK)) < 0) {
          snprintf(dst, sizeof(dst), "/usr/bin/%s", args[0]);
          if((access(dst, X_OK)) < 0) {
            printf("cannot access\n");
          }
        }

        if((execv(dst, args)) < 0) {
          printf("%s\n", dst);
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
