#include <stdio.h>
#include <stdlib.h>
#include <brainfuck.h>


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

