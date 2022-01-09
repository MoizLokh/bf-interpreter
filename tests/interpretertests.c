#include <stdio.h>
#include <stdlib.h>

#include <acutest.h>
#include <brainfuck.h>
#include <files.h>

#define NUM_TEST  1

FILE* outfile;
char* tests[NUM_TEST] = {"../tests/testcases/HelloWorld.txt"};
char* expt[NUM_TEST] = {"Hello, World"};

void test_init(void) {
  //TEST_CHECK(1 != 1);
  outfile = fopen("testcases/output", "w");
}

void test_output(void) {
  FILE* fptr;
  int error;
  char* inst;
  char* out;
  
  for (int i = 0; i < NUM_TEST; i++) {
    inst = fileToString(tests[i], &error);
    if (error == -1) TEST_ASSERT(0);

    printf("%s", inst);
    
    if (bf_interpreter(inst, outfile) == -1) TEST_ASSERT(0);
    
    out = fileToString("testcases/output.txt", &error);
    if (error == -1) TEST_ASSERT(0);

    TEST_ASSERT(out == expt[i]); // is the output as expected

    free(out);
    free(inst);
  }
}

void test_end(void) {
  fclose(outfile);
}

TEST_LIST = {
  {"INIT", test_init},
  {"OUTPUT", test_output},
  {"END", test_end},
  {0}
};
