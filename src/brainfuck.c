#include <stdio.h>
#include <stdlib.h>

void bf_interpreter(char *buf, size_t size);

void bf_interpreter(char *buf, size_t size) {
  
  return;
}

int main(int argc, char *argv[]) {
  FILE *fptr;
  size_t fsize;
  char *buffer;
  
  if (argc < 2) {
    printf("Missing file argument \n");
    exit(1); 
  }
  
  fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    printf("Failed to open file \n");
    exit(1);
  }

  fseek(fptr, 0, SEEK_END);
  fsize = ftell(fptr);
  rewind(fptr);

  // Initialize a buffer
  buffer = malloc(fsize);
  if (!buffer) {
    printf("Failed to allocate memory");
    free(buffer);
    fclose(fptr);
    exit(1);
  }

  // Add file contents into buffer
  if (fread(buffer, fsize, 1, fptr) == 0) {
    printf("Failed to read file");
    free(buffer);
    fclose(fptr);
    exit(1);
  }

  fclose(fptr);
  //bf_interpreter(buffer);
  free(buffer);
  
  return 0;
}

