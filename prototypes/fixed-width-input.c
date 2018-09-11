#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program will receive long strings of input and
 * insert newlines at the nearest space before the
 * line length limit. If line length is exceeded, input will be trimmed,
 * and the user will be notified.
 */

#define MAX_LINE_LENGTH 50

int find_space(char *input, int start, int end) {
  /* Search for spaces in input before end
   * and return the number of the index. */
  int i = 0;
  for (i = start; i < end; i++) {
    if (input[MAX_LINE_LENGTH - i] == ' ')
      return MAX_LINE_LENGTH - i;
  }
  return MAX_LINE_LENGTH; // fallthrough in case string contains no spaces
}

char *insert_newlines(char *input) {


  return input;
}

int main(int argc, char *argv[]);
