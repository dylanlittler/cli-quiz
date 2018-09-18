#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_processor.h"

/** This program will display a character count while the
 * user is typing, then echo the input back to the screen
 * in fixed width columns. This file contains the main
 * function which runs char-count.c to display
 * character count, then fixed-width-input.c to
 * divide lines into fixed width.
 */

int main(int argc, char *argv[]) {
  int max_input;
  int max_line_length;
  if (argc == 3) {
    max_line_length = atoi(argv[1]);
    max_input = atoi(argv[2]);
  } else if (argc == 1) {
    max_line_length = 50;
    max_input = 200; // reasonable default values
  } else {
    printf("USAGE: input-processor max_length max_input\n");
    return 1;
  }

  if (max_line_length > max_input) {
    printf("max_input must be a larger than max_length\n");
    return 1;
  }

  // add check for NULL return value
  char *user_input = handle_input(max_line_length, max_input);

  printf("\nYour input:\n%s\n", user_input);
  
  free(user_input);
  return 0;
}

