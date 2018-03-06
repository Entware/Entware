#include <stdio.h>

int main() {
  int test = 0;
  char *bytes = (char *) &test;
  *bytes = 0x1;

  printf("Byte Order: ");
  if (test == 1){
    printf("little endian.\n");
    return 1;
  }
  else {
      printf("big endian.\n");
      return 0;
  }
}

