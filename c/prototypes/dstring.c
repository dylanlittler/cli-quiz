#include <stdlib.h>
#include <string.h>

/**
 * The function in this program expands the memory of
 * a variable by copying the contents, destroying the
 * previously memory, and allocating a new, larger chunk.
 */

void Expand_String(char *string, int new_size) {
  string = realloc(string, new_size);
  /*char *temp = string;
  free(string);
  string = malloc(new_size);
  memcpy(string, temp, strlen(temp));*/
}
