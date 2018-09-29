#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raw_mode.h"

/**
 * Tests function Expand_String() from dstring.c.
 */

int main() {
  enable_raw_mode();
  int string_size = 20;
  char *test_string = malloc(string_size);
  //printf("Address at start of program: %p\n", &test_string);
  int c, chars = 0;

  while ((c = getchar()) != '\n') {
    test_string[chars] = c;
    chars++;

    if (chars >= string_size) {
      string_size += 20;
      test_string = realloc(test_string, string_size);
      //Expand_String(test_string, string_size);
      //printf("Address after calling function: %p\n", &test_string);
    }
  }
  test_string[chars] = '\0';
  printf("Your input: %s\nChars: %d\n", test_string, chars);

  free(test_string); // invalid free here
  return 0;
}
