#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program will receive long strings of input and
 * insert newlines at the nearest space before the
 * line length limit, which is designed to reflect a length
 * That will fit in a standard terminal.
 * If maximum input length is exceeded, input will be trimmed,
 * and the user will be notified.
 */

#define MAX_LINE_LENGTH 50 // most terminal screens are longer than this
#define MAX_INPUT 200

int find_space(char *input, int end) {
  /* Search for spaces in input before end
   * and return the number of the index. */
  int i = 0;
  for (i = 0; i < MAX_LINE_LENGTH; i++) {
    if (input[end - i] == ' ')
      return end - i;
  }
  return end; // fallthrough in case string contains no spaces
}

char *insert_newlines(char *input) {
  /* A newline will be inserted at a space at intervals as close to
   * MAX_LINE_LENGTH as possible. Iteration will continue as long
   * as the remaining string exceeds this limit.
   */

  int line_end = MAX_LINE_LENGTH;
  int line_start = 0;

  for (line_start = 0; line_start <= strlen(input); line_start += MAX_LINE_LENGTH) {
    if (strlen(input) - line_start <= MAX_LINE_LENGTH) {
      return input; // break the loop if inserting newline is not needed
    } else {
      line_end = find_space(input, line_end);
      input[line_end] = '\n';
      line_end += MAX_LINE_LENGTH;
    }
  }
  return input;
}

int main(int argc, char *argv[]) {
  char *user_input = malloc(MAX_INPUT);
  memset(user_input, 0, MAX_INPUT);
  int c, chars;

  chars = 0;
  while ((c = getchar()) != '\n') {
    if (chars >= MAX_INPUT - 1) {
      printf("Maximum input exceeded. Your input will not be saved.\n");
      free(user_input);
      exit(1);
    }
    user_input[chars] = c;
    chars++;
  }
  insert_newlines(user_input);
  printf("Your input:\n%s\n", user_input);
  
  free(user_input);
  return 0;
}
