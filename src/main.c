#include <stdio.h>
#include <stdlib.h>
#include <brainfuck.h>


int main(int argc, char *argv[]) {
  FILE *fptr;
  size_t fsize;
  char *buffer;
  long offset = 0;

  // Initilize a stack pointer
  stptr = stack;
  
  if (argc < 2) {
    perror("Missing file argument \n");
    exit(1); 
  }
  
  fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    perror("Failed to open file \n");
    exit(1);
  }

  fseek(fptr, 0, SEEK_END);
  fsize = ftell(fptr);
  rewind(fptr);

  // Initialize a buffer
  buffer = malloc((fsize + 1) * sizeof(char));
  if (!buffer) {
    perror("Failed to allocate memory");
    free(buffer);
    fclose(fptr);
    exit(1);
  }

  while (!feof(fptr) && offset < fsize) {
    //increment the file offset depending on how much we read
    offset += fread(buffer + offset, sizeof(char), fsize - offset, fptr);
  }
  buffer[offset] = '\0';

  fclose(fptr);
  bf_interpreter(buffer);
  free(buffer);
  
  return 0;
}

