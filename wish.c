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
      } 
      int rc = fork();
      if(rc < 0) {
	fprintf(stderr, "fork failed\n");
	exit(1);
      }else if(rc == 0) {
      	// ここでコマンドを実行
	char *myargs[3];
	myargs[0] = strdup(".");
	myargs[1] = NULL;
	if((execv("/bin/ls", myargs)) < 0) {
	  fprintf(stderr, "execv failed\n");
	  exit(1);
	};
	fwrite(line, linelen, 1, stdout);
	exit(0);
      } else {
      	wait(NULL);
      }
    }
  }
  return 0;
}
