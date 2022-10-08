#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <brainfuck.h>
#include <files.h>

const char* optstring = "f:";

int main(int argc, char *argv[]) {
  
  char *buffer;
  int num_read;
  char opt;
  int filemode = 0;
  
  // Initilize a stack pointer
  stptr = stack;

  opterr = 0;

  if (argc == 1) {
    printf("Missing file argument \n");
    return -1;
  }

  while ((opt = getopt(argc, argv, optstring)) != -1) {
    switch((char)opt)
      {
      case 'f':
        filemode = 1;
	break;

      case '?':
	printf("Option %c is not valid \n", optopt);
	return -1;
      }
  }
  
  if (filemode) buffer = fileToString(argv[1], &num_read);
  else buffer = argv[optind];
  if (num_read == -1) {
    return -1;
  }
  
  bf_interpreter(buffer, stdout);
  free(buffer);
  
  return 0;
}

