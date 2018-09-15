#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input-processor.h"

/** This program will display a character count while the
 * user is typing, then echo the input back to the screen
 * in fixed width columns. This file contains the main
 * function which runs char-count.c to display
 * character count, then fixed-width-input.c to
 * divide lines into fixed width.
 */

int main(int argc, char *argv[]) {
  int max_input;
  int max_length;
  if (argc == 3) {
    max_length = atoi(argv[1]);
    max_input = atoi(argv[2]);
  } else if (argc == 1) {
    max_length = 50;
    max_input = 200; // reasonable default values
  } else {
    printf("USAGE: input-processor max_length max_input\n");
    return 1;
  }

  if (max_length > max_input) {
    printf("max_input must be a larger than max_length\n");
    return 1;
  }

  char *user_input = malloc(max_input);
  memset(user_input, 0, max_input);

  count_characters(user_input, max_input);

  insert_newlines(user_input, max_length);

  printf("\nYour input:\n%s\n", user_input);
  
  free(user_input);
  return 0;
}

