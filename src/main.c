#include <stdio.h>
#include <stdlib.h>
#include <brainfuck.h>
#include <files.h>


int main(int argc, char *argv[]) {
 
  char *buffer;
  int num_read;

  // Initilize a stack pointer
  stptr = stack;
  
  if (argc < 2) {
    printf("Missing file argument \n");
    return -1;
  }

  buffer = fileToString(argv[1], &num_read);
  if (num_read == -1) {
    return -1;
  }
  
  bf_interpreter(buffer);
  free(buffer);
  
  return 0;
}

