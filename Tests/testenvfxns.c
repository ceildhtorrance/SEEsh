#include <stdio.h>
#include <stdlib.h>

int main() {
  char *value;
  value = getenv("HOME");
  printf("HOME= %s\n", value);
  value = getenv("USER");
  printf("USER= %s\n", value);
  value = getenv("PASSWORD");
  printf("PASSWORD= %s\n", value);
}
