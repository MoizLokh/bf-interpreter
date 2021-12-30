#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 100

int mem[MEM_SIZE];

void bf_interpreter(char *buf, size_t size);

void bf_interpreter(char *buf, size_t size) {
  int index = 0;
  int memIndex = 0;
  
  while (index < size) {
    switch(buf[index]) {
    case '+':
      mem[memIndex]++;
      break;

    case '-':
      mem[memIndex]--;
      break;

    case '>':
      if (memIndex < 99) memIndex++;
      break;

    case '<':
      if (memIndex > 0) memIndex--;
      break;

    case '.':
      printf("%c", mem[memIndex]);
      //puts((char*) mem[memIndex]);
      break;
    }
    index++;
  }
  return;
}

int main(int argc, char *argv[]) {
  FILE *fptr;
  size_t fsize;
  char *buffer;
  long offset = 0;
  
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

  fclose(fptr);
  bf_interpreter(buffer, fsize);
  free(buffer);
  
  return 0;
}

