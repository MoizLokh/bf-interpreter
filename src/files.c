#include <stdio.h>
#include <stdlib.h>
#include <files.h>


/* Function: fileToString
 *  ----------------------
 *  Allocates memory for a string and reads data of file
 *  into it, ignores line breaks.
 * 
 *  file_name: Name of the file to read. Should contain .txt file extension.
 *  num_read:The number of bytes read
 *           returns -1 if error
 *  
 *  return: String containing contents from the file. Make sure to use free
 *          to avoid memory leaks only if num_read is not -1.
 */

char* fileToString(char* file_name, int* num_read) {

  char* buffer;
  size_t fsize;
  FILE *fptr;
  long offset = 0;
  
  fptr = fopen(file_name, "r");
  if (fptr == NULL) {
    printf("Failed to open file \n");
    *num_read = -1;
    return buffer;
  }

  fseek(fptr, 0, SEEK_END);
  fsize = ftell(fptr);
  rewind(fptr);

  // Initialize a buffer
  buffer = malloc((fsize + 1) * sizeof(char));
  if (!buffer) {
    printf("Failed to allocate memory");
    free(buffer);
    fclose(fptr);
    *num_read = -1;
    return buffer;
  }

  while (!feof(fptr) && offset < fsize) {
    //increment the file offset depending on how much we read
    offset += fread(buffer + offset, sizeof(char), fsize - offset, fptr);
  }
  buffer[offset] = '\0';

  fclose(fptr);
  return buffer;
}

