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

#define MAX_LINE_LENGTH 50 // set line limit for memory allocation purposes

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

int main(int argc, char *argv[]) {
  enable_raw_mode();

  int c, chars;
  char *input = malloc(MAX_LINE_LENGTH);
  memset(input, 0, MAX_LINE_LENGTH);

  chars = 0;
  printf("Please type your text below. Limit is %d\n", MAX_LINE_LENGTH);
  while ((c = getchar()) != '\n') {
    if (chars >= MAX_LINE_LENGTH - 1) { // ensure that memory limit will not be exceeded
      printf("\nCharacter limit has been exceeded. Your input will not be saved.\n");
      free(input); // free variable if program is forced to abort
      exit(1);
    }
    input[chars] = c; //append new character to input
    chars++; // increment now so that count will be accurate

    printf("\rchars %d %s", chars, input); // reprint input, overwriting current input
    fflush(stdout);
  }
  printf("\n");

  free(input); // free input variable if program runs successfully

  return 0;
}
