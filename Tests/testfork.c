#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  pid_t pid;
  pid = getpid();
  printf("The PID of this process is: %d\n", pid);

  pid = fork();
  if(pid==0) {
    printf("This is the child process with fork returning PID: %d\n", pid);
    sleep(10);
  } else if (pid <0) {
    printf("Error forking: ");
  } else {
    printf("This is the parent with fork returning PID: %d\n", pid);
    wait(NULL);
  }
}
