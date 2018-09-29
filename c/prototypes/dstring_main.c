#include "dstring.h"
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

  int c, chars = 0;

  while ((c = getchar()) != '\n') {
    test_string[chars] = c;
    chars++;

    if (chars >= string_size) {
      string_size += 20;
      Expand_String(test_string, string_size);
    }

  }

  printf("Your input: %s\nChars: %d\n", test_string, chars);

  free(test_string);
  return 0;
}
