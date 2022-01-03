#ifndef BF_H
#define BF_H

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

#endif // BF_H
