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
  for (i = 0; i < MAX_LINE_LENGTH; i++) {
    if (input[end - i] == ' ')
      return end - i;
  }
  return end; // fallthrough in case string contains no spaces
}

char *insert_newlines(char *input) {
  int line_end = MAX_LINE_LENGTH;
  int line_start = 0;
  int prev_line_end = 0;

  for (line_start = 0; line_start <= strlen(input); line_start += MAX_LINE_LENGTH) {
    if (strlen(input) - line_start <= MAX_LINE_LENGTH) {
      return input;
    } else {
      line_end = find_space(input, prev_line_end, line_end);
      input[line_end] = '\n';
      prev_line_end = line_end;
      line_end += MAX_LINE_LENGTH;
      printf("Line_start: %d, line_end: %d, prev_line_end: %d\n",
	     line_start, line_end, prev_line_end);
    }
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
