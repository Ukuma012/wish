#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// BUGGY!!!!!!!!!

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
      printf("hello world (pid:%d)\n", (int) getpid());
      int rc = fork();
      if(rc < 0) {
	fprintf(stderr, "fork failed");
	exit(1);
      }else if(rc == 0) {
	printf("hello I am child (pid:%d)\n", (int) getpid());
      } else {
	printf("hello I am parent of %d (pid:%d)\n", rc, (int) getpid());
      }
      fwrite(line, linelen, 1, stdout);
      line = NULL;
    }
  }
  return 0;
}
