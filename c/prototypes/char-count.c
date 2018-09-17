#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raw_mode.h"

/* This program will provide a live character count of
 * the user's input by adding each character to a variable
 * and printing out from the start of the line.
 * Terminal settings must be changed to achieve this,
 * as characters will otherwise not be received by the program
 * until the user hits enter, or line length limit is exceeded,
 * in which case a newline will be appended, program will finish,
 * and the user will be notified.
 */


void count_characters(char *input, int max_input) {
  enable_raw_mode();

  int c, chars;

  clear_screen();
  printf("Screen cleared to allow for multiple line input.\n");

  printf("Please type your input below. Limit is %d.\n", max_input);
  
  chars = 0;

  printf("\033[s"); // save cursor position
  
  printf("chars % 4d/%03d ", chars, max_input);
  while ((c = getchar()) != '\n') {
    if (chars >= max_input - 1) { // ensure that memory limit will not be exceeded
      printf("\nCharacter limit has been exceeded.\n");
      return;
    }
    if (c == 127) { // handle backspace
      if (chars == 0) // prevents errors caused by initial backspace, then insert
	continue;
      chars--;
      input[chars] = 0;
      printf("\033[1D \033[1D");
    } else {
      input[chars] = c; //append new character to input
      chars++; // increment now so that count will be accurate
    }

    /* This function call will restore original cursor position, save it again,
    * then print output, to allow cursor to start at original position
    * in case of input that exceeds one line.
    */
    printf("\033[u\033[schars % 4d/%03d %s", chars, max_input, input);
  }
  printf("\n");

  return;
}
