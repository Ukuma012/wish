#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// @TODO redirection
// @TODO GUI
// @TODO 処理を関数にまとめる
// @TODO cd実装

int main(int argc, char *argv[])
{
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  char *whitespace = " \t";

  while (1)
  {
    char *args[10];
    char *string;
    int i = 0;

    int j = 0;
    char *path;
    char *patharg[10];
    char *pathline;
    char cwd[256];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
      fprintf(stderr, "getcwd failed\n");
      exit(1);
    }
    pathline = cwd;
    while ((path = strsep(&pathline, "/")) != NULL)
    {
      patharg[j] = path;
      j++;
    }

    printf("%s %s", patharg[j - 1], " wish> ");
    if ((linelen = getline(&line, &linecap, stdin)) > 0)
    {
      // 末尾の改行を終端に変更
      char *p;
      p = strchr(line, '\n');
      if (p != NULL)
      {
        *p = '\0';
      }

      while ((string = strsep(&line, whitespace)) != NULL)
      {
        if (*string == '\0')
        {
          continue;
        }
        args[i] = string;
        i++;
      }
      args[i] = NULL;

      if (strcmp(args[0], "exit") == 0)
      {
        exit(0);
      }

      int rc = fork();
      if (rc < 0)
      {
        fprintf(stderr, "fork failed\n");
        exit(1);
      }
      else if (rc == 0)
      {
        char cmd[20];
        snprintf(cmd, sizeof(cmd), "/bin/%s", args[0]);
        if ((access(cmd, X_OK)) < 0)
        {
          snprintf(cmd, sizeof(cmd), "/usr/bin/%s", args[0]);
          if ((access(cmd, X_OK)) < 0)
          {
            fprintf(stderr, "command not found\n");
            exit(1);
          }
        }

        if ((execv(cmd, args)) < 0)
        {
          printf("%s\n", args[0]);
          fprintf(stderr, "execv failed\n");
          exit(1);
        }
        exit(0);
      }
      else
      {
        wait(NULL);
      }
    }
  }
  return 0;
}
