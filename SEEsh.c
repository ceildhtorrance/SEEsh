/*
 * Ceilidh Torrance
 * V00885432
 * Assignment 1 - SEEsh.c
 * CSC 360
*/

#include <stdio.h>
#include <stdlib.h> //malloc
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * Function declarations
*/
int cd(char *tokens);
int pwd(char *tokens);
int help(char *tokens);
int set(char *tokens);
int unset(char *tokens);

/*
 * global variable declarations
*/
int bi_size = 5;
pid_t pid;

/*
 * set of built-in commands
*/
char *builtin[] = {
  "cd",
  "pwd",
  "help",
  "set",
  "unset"
};

/*
 * set of built-in functions corresponding to the commands
*/
int (*function[])(char *) = {
  &cd,
  &pwd,
  &help,
  &set,
  &unset
};

/*
 * cd() changes working directory for process to new directory as specified by user
 * returns an error message if the path is invalid
*/
int cd(char *tokens) {
  tokens = strtok(NULL, " \n");
  if(chdir(tokens) == -1) {
    perror("Invalid path");
  }
  return 0;
}

/*
 * pwd() prints out the current directory
*/
int pwd(char *tokens) {
  char path[100];
  printf("%s\n", getcwd(path, 100));
  return 0;
}


/*
 * help() prints information about the built-in commands
*/
int help(char *tokens) {
  printf("The built in commands are as follows:\n");
  printf("cd <path>         : changes working directory to path as specified, returns error message if path is invalid\n");
  printf("pwd               : prints working directory for process\n");
  printf("help              : provides information about the built in commands\n");
  printf("set <var> <value> : sets an enviroment variable to specified value, if one does not already exist with that name, it will be created\n");
  printf("unset <var>       : specified environment variable will be destroyed\n");
  printf("exit              : process will terminate\n\n");
  return 0;
}

/*
 * set() changes value of variable passed in if it already exists
 * or creates a new variable with var and sets it to val if it does not exist
*/
int set(char *tokens) {
  char *var = tokens;
  var = strtok(NULL, " \n");
  char *val = tokens;
  val = strtok(NULL, " \n");
  if(setenv(var, val, 1) == -1) {
    perror("Error in setting envrionment variable");
  } else {
    val = getenv(var);
    printf("Environment variable set successful: %s= %s\n", var, val);
  }
  return 0;
}

/*
 * unset() removes the specified enriromnet variable if it exitst
*/
int unset(char *tokens) {
  tokens = strtok(NULL, " \n");
  if(unsetenv(tokens) == -1) {
    perror("Error unsetting environment variable");
  } else {
    printf("Envrionment variable successfully unset\n");
  }
  return 0;
}

/*
 * split_args() splits the tokenized string and stores the words
 * in an array so they can be passed to exec as arguments
*/
char **split_args(char *tokens) {
  int bufsize = 64, i = 0;
  char **args = malloc(bufsize * sizeof(char*));
  if(!args) {
    perror("Allocation error");
    exit(0);
  }

  while(tokens!= NULL) {
    args[i] = tokens;
    i++;

    if (i >= bufsize) {
      bufsize += 64;
      args = realloc(tokens, bufsize *sizeof(char*));
      if (!args) {
        perror("Allocation error");
        exit(0);
      }
    }
    tokens = strtok(NULL, " \n");
  }
  args[i] = NULL;
  return args;
}

/*
 * fork_child() creates a child process to run a program if the command entered
 * does not match one of the built in commands. Exec is used to run the command.
 * The parent process will wait for the child to complete.
*/
int fork_child(char *tokens) {
  pid=fork();
  if(pid == 0) {
    char **args = split_args(tokens);

    if(execvp(args[0], args) == -1) {
      perror("Error forking");
    }
    exit(0);
  } else if(pid < 0) {
    perror("Error in forking child");
  } else {
    wait(&pid);
  }
  return 0;
}

/*
 * read_str looks at the first token and determines if it is a built
 * in command or if it needs to launch a child to execute
 * NEEDS TO REFERENCE THE TUTORIAL AS IT IS VERY SIMILAR
 */
int read_str(char *tokens) {
  if(tokens == NULL) {
    printf("\n");
    exit(0);
  }

  for(int i = 0; i < bi_size; i++) {
    if(strcmp(tokens, builtin[i]) == 0) {
      return (*function[i])(tokens);
      //if match is found, should pass off to built-in command
    }
  }
  return fork_child(tokens);
}

/*
 * seeshrc_loop reads the .SEEshrc file one line at a time. After each line it calls
 * the read_string function to read the line and execute the command.
*/
void seeshrc_loop(FILE *fp) {
  char *tokens;
  char c[1000];

  while(fgets(c, sizeof(c), fp) != NULL) {
    printf("\nCommand from .SEEshrc: %s", c);
    /*tokenize user input*/
    tokens = strtok(c, " \n");
    read_str(tokens);
  }
}

/*
 * cmd_loop reads input from the command line, tokenizes it, and then
 * passes it off to be interpreted by read_str()
*/
void cmd_loop() {
  char *readLine = NULL;
  size_t size = 0;
  char *tokens;

  /*do loop executes until cntl-D or "exit" is typed*/
  do {
    /*retrieve user input*/
    printf("? "); //user input prompt

    if (feof(stdin)) {
      printf("\n");
      exit(0);
    }

    getline(&readLine, &size, stdin); //retrieve user input

    if(!strncmp(readLine, "exit", 4)) {
      exit(0);
    }
    /*tokenize user input*/
    tokens = strtok(readLine, " \n");

    read_str(tokens);
  } while (strncmp(readLine, "exit", 4));
}


/*
 * signal code to override Ctrl-C command for parent SEEsh process
 * checks pid, if parent process, Ctrl-C will be passed over
 * if child process, Ctrl-C will exit the process, but not the whole program
*/
void sigintHandler(int sig_num)
{
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler);
    if(pid == 0) {
      exit(0);
    }
    printf("\n? ");
    fflush(stdout);
}

/*
 * main() first calls seeshrc_read, to read and execute the commands in SEEshrc
 * main() then calls the command loop to read user input
*/
int main() {
  signal(SIGINT, sigintHandler); //signal code to override Ctrl-C command for parent SEEsh process
  FILE *fp;
  if((fp = fopen(".SEEshrc", "r")) == NULL) {
    perror("Error opening file");
  }
  seeshrc_loop(fp);
  fclose(fp);

  pid = getpid();
  cmd_loop();
}
