#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program will receive long strings of input and
 * insert newlines at the nearest space before the
 * line length limit. If line length is exceeded, input will be trimmed,
 * and the user will be notified.
 */

#define MAX_LINE_LENGTH 50
#define MAX_INPUT 200

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
  int line_end = strlen(input);
  int line_start = 0;
  if (strlen(input) <= MAX_LINE_LENGTH) {
    return input;
  } else {
    line_end = find_space(input, line_start, line_end);
    input[line_end] = '\n';
  }
  return input;
}

int main(int argc, char *argv[]) {
  char *user_input = malloc(MAX_INPUT);
  memset(user_input, 0, MAX_INPUT);
  int c, chars;

  chars = 0;
  while ((c = getchar()) != '\n' && chars < MAX_INPUT - 1) {
    user_input[chars] = c;
    chars++;
  }
  insert_newlines(user_input);
  printf("Your input:\n%s\n", user_input);
  
  free(user_input);
  return 0;
}
