#include <stdio.h>
#include <stdlib.h>


void bf_interpreter(FILE *fptr) {
  return;
}

int main(int argc, char *argv[]){

  if (argc < 2) {
    printf("Missing file argument \n");
    return 0; 
  }
  
  FILE *fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    printf("Failed to open file \n");
    return 0;
  }

  bf_interpreter(fptr);
                                   
  fclose(fptr);
  return 0;
}

