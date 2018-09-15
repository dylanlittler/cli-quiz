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

int find_space(char *input, int end, int max_length) {
  /* Search for spaces in input before end
   * and return the number of the index. */
  int i = 0;
  for (i = 0; i < max_length; i++) {
    if (input[end - i] == ' ')
      return end - i;
  }
  return end; // fallthrough in case string contains no spaces
}

void insert_newlines(char *input, int max_length) {
  /* A newline will be inserted at a space at intervals as close to
   * MAX_LINE_LENGTH as possible. Iteration will continue as long
   * as the remaining string exceeds this limit.
   */

  int line_end = max_length;
  int i = 0;

  // loop runs as long as there are max_length long blocks to split
  for (i = 0; i <= strlen(input); i += max_length) {
    if (strlen(input) - i <= max_length) {
      break;
    } else {
      line_end = find_space(input, line_end, max_length);
      input[line_end] = '\n';
      line_end += max_length;
    }
  }
}
