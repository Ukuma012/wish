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
	// /bin/lsが引数を取らない場合、後にスペースが必要になっている
	// /bin/ls ./testsは成功
	char *string;
	char *myargs[3];
	int i = 0;
	while((string = strsep(&line, " ")) != NULL) {
	  myargs[i] = string;
	  i++;
	}
	//myargs[1] = "./tests";
	myargs[2] = NULL;
	printf("%s", myargs[0]);
	if((execv(myargs[0], myargs)) < 0) {
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
