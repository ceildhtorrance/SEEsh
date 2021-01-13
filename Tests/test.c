#include <stdio.h>
#include <stdlib.h> //malloc
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/*int main(int argc, char **argv, char **envp) {
  char *readLine = {"There are 5 tokens here"};
  char *tokens = strtok(readLine, " \n");
  char *test = tokens;
  int count = 0;
  while(test != NULL) {
    count++;
    test = strtok(NULL, " \n");
  }
  while(tokens != NULL) {
    printf("%s/", tokens);
    tokens = strtok(NULL, " \n");
  }
  printf("\ncount: %d\n", count);
}*/
/*void sighandler(int);
int k = 0;

int test() {
  while(1) {
     printf("Going to sleep for a second...\n");
     sleep(1);
  }
  return(0);
}

int main () {
   signal(SIGINT, sighandler);

   test();
   return(0);
}

void sighandler(int signum) {
  if(k != 0) {
    exit(1);
  }

   printf("Caught signal %d, coming out...\n", signum);
   //exit(1);
}*/

int  main(void)
{
     while (1) {
      printf("Print\n");
      pause();
     }
}
