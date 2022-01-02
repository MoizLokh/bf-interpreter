#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 100
#define MAX_LOOPS 1000

char* stack[MAX_LOOPS];
char** stptr;

char mem[MEM_SIZE];

// Function-like Macros for stack
#define push(stptr, n) (*(stptr += sizeof(char*)) = (n))
#define pop(stptr) (*(stptr -= sizeof(char*)))
#define top(stptr) (*stptr)

void bf_interpreter(char *instr);
void endLoop(char *instr);


void bf_interpreter(char *instr) {
  int index = 0;
  int open_loops = 0;
  
  while (*instr != '\0') {
    switch(*instr) {
    case '+':
      mem[index]++;
      break;

    case '-':
      mem[index]--;
      break;

    case '>':
      if (index < 99) index++;
      break;

    case '<':
      if (index > 0) index--;
      break;

    case '.':
      putchar(mem[index]);
      //puts((char*) mem[index]);
      break;

    case ';':
      scanf("%c", &mem[index]);
      break;

    case '[':
      // If data is 0 then we skip the loop 
      if (mem[index] == 0) endLoop(instr);
      else {
	open_loops++;
	// Push instr ptr that we would return to at the end of an iteration
	push(stptr, instr);
      }      
      break;

    case ']':
      // Check if no loops are open, otherwise error
      if (open_loops == 0) {
	perror("\n Closing loop that was never opened");
	return;
      }

      /* Loops back if memory locationc contains zero
	 Instr pointer modified to one we saved when opening loop */
      if (mem[index] == 0) open_loops--, pop(stptr);
      else instr = top(stptr);	
      break;      
    }
    
    instr++;
  }
  return;
}

void endLoop(char* instr) {
  int open_loops = 0;
  
  while (*instr != '\0') {
    switch(*instr) {
    case '[':
      open_loops++;
      break;

    case ']':
      if (open_loops == 0) return;
      else open_loops--;
      break;
    }
    instr++;
  }
}

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

