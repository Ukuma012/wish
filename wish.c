#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  char error_message[30] = "An error has occurred\n";

  while(1) {
    printf("wish> ");
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
        // cat wish.cのような感じで動くようになった
	// 動的なargs配列確保をすれば良い？

	char *args[3];
	char dst[20];
	char *string;
	int i = 0;
	while((string = strsep(&line, " ")) != NULL) {
		args[i] = string;
		i++;
	}
	args[i] = NULL;

	snprintf(dst, sizeof(dst), "/bin/%s", args[0]);
	if((access(dst, X_OK)) < 0) {
	  printf("cannot access /bin/\n");
	  snprintf(dst, sizeof(dst), "/usr/bin/%s", args[0]);
	  if((access(dst, X_OK)) < 0) {
	    printf("cannot access /usr/bin/\n");
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
