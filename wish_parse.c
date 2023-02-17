#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 100
#define MAXARGS 10

struct cmd {
  char *argv[MAXARGS];
  char *eargv[MAXARGS];
};

char *get(char *, int);
int getcmd(char *, int);
void exec(struct cmd *);
int gettoken(char**, char*, char**, char**); 

char *get(char *buf, int max) {
  int c, i;
  for(i = 0; i+1 < max; ) {
    c = fgetc(stdin);
    if(c == '\n')
      break;
    if(c < 0) 
      break;
    buf[i++] = c;
  }
  buf[i] = '\0';
  return buf;
}

int getcmd(char *buf, int nbuf) {
  // @TODO 今自分がどこにいるのか表示
  printf("%s", "wish> ");
  get(buf, nbuf);
  if(buf[0] == 0)
    return -1;
  return 0;
}

void exec(struct cmd *cmd) {
  // @TODO nulterminate実装 
  if(cmd->argv[0] == 0)
    exit(0);
  // @TODO accessシステムコールで確認
  if((execv(cmd->argv[0], cmd->argv)) < 0) {
    fprintf(stderr, "execv failed\n");
    exit(1);
  }
  exit(0);
}

struct cmd* parse(char *s) {
 char *es;
 char *q;
 char *eq;
 int tok, argc;
 struct cmd *ret;

 // esは\0を指す
 es = s + strlen(s);
 argc = 0;
 while(1) {
  if((tok = gettoken(&s, es, &q, &eq)) == 0) {
    break;
  }
  ret->argv[argc] = q;
  ret->eargv[argc] = eq;
  argc++;
  if(argc >= MAXARGS)
    fprintf(stderr, "too many argument");
    exit(1);
  }
  ret->argv[argc] = 0;
  ret->eargv[argc] = 0;
  return ret;
 }

int gettoken(**ps, *es, **q, **eq) {
  char *s;
  int ret;

  s = *ps;
  while(s < es && strchr(" ", *s))
    s++;
  if(q)
    *q = s;
  ret = *s;
  switch(*s){
    case 0:
      break;
    default:
      while(s < es && !strchr(" ", *s) )
        s++;
      break;
  }
  if(eq)
    *eq = s;

  while(s < es && strchr(" ", *s))
    s++;
  *ps = s;
  return ret;
}

int main(int argc, char *argv[]) {
  char buf[BUFSIZE];
  while(getcmd(buf, sizeof(buf)) >= 0) {
    if(buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'i' && buf[3] == 't') 
      exit(0);

    int rc = fork();
    if(rc < 0) {
      fprintf(stderr, "fork failed\n");
      exit(1);
    } else if(rc == 0) {
      // @TODO exec
      // @TODO parse
      printf("Hi! I am child\n");
      exit(0);
    } else {
      wait(NULL);
      printf("Hi! I am parent\n");
    }
  }
  return 0;
}
