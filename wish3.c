#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define default 0
#define redirection 1

// @TODO GUI
// @TODO 処理を関数にまとめる
// @TODO tab補完

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
    char *patharg[256];
    char *pathline;
    char cwd[256];

    int type = default;
    char *dst;

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

    printf("%s %s %s", patharg[j - 1], "%", "wish> ");
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

      if (strcmp(args[0], "cd") == 0)
      {
        if (i > 2)
        {
          fprintf(stderr, "too many argument\n");
          continue;
        }
        if (chdir(args[1]) < 0)
        {
          fprintf(stderr, "no such file of directory\n");
        }
        continue;
      }

      // parseして、forkするときに処理を変える
      for (int h = 0; h < i; h++)
      {
        if (strcmp(args[h], ">") == 0)
        {
          type = redirection;
          dst = args[h + 1];
          args[h] = NULL;
          continue;
        }
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

        if (type == default)
        {
          if ((execv(cmd, args)) < 0)
          {
            printf("%s\n", args[0]);
            fprintf(stderr, "execv failed\n");
            exit(1);
          }
          exit(0);
        } else if(type == redirection) {
          close(STDOUT_FILENO);
          open(dst, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
          if ((execv(cmd, args)) < 0)
          {
            printf("%s\n", args[0]);
            fprintf(stderr, "execv failed\n");
            exit(1);
          }
          exit(0);
        }
      }
      else
      {
        wait(NULL);
      }
    }
  }
  return 0;
}