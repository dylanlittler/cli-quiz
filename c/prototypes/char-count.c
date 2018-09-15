#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program will provide a live character count of
 * the user's input by adding each character to a variable
 * and printing out from the start of the line.
 * Terminal settings must be changed to achieve this,
 * as characters will otherwise not be received by the program
 * until the user hits enter, or line length limit is exceeded,
 * in which case a newline will be appended, program will finish,
 * and the user will be notified.
 */


struct termios orig_termios; // struct to save original terminal settings

void disable_raw_mode() {
  /* Restore original terminal settings. */
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
  /* Turn off canon mode in terminal
   * so that keystrokes are sent to the program. */

  // Save original terminal settings
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disable_raw_mode); // ensure settings are restored

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON); // Stop terminal from processing input

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void count_characters(char *input, int max_input) {
  enable_raw_mode();

  int c, chars;

  chars = 0;
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
    printf("\rchars % 4d/%03d %s", chars, max_input, input); // reprint input, overwriting current input
  }
  printf("\n");

  return;
}
