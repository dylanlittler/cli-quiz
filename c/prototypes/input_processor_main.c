#include <stdio.h>
#include <stdlib.h>
#include "bstrlib.h"
#include "input_processor.h"
#include "dbg.h"

/** This program will display a character count while the
 * user is typing, then echo the input back to the screen
 * in fixed width columns. This file contains the main
 * function which runs char-count.c to display
 * character count, then fixed-width-input.c to
 * divide lines into fixed width.
 */

int main(int argc, char *argv[]) {
  int max_line_length;
  if (argc > 1) {
    max_line_length = atoi(argv[1]);
  } else {
    max_line_length = 50; // default length to fit terminal width
  }
  
  bstring user_input = handle_input(max_line_length);
  
  printf("\nYour input:\n%s\n", bdata(user_input));
  
  bdestroy(user_input);
  return 0;
}

