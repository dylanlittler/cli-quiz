#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

/** This program will receive long strings of input and
 * insert newlines at the nearest space before the
 * line length limit, which is designed to reflect a length
 * That will fit in a standard terminal. Character count
 * will be updated as the user types.
 * Terminal settings must be changed to achieve this,
 * as characters will otherwise not be received by the program.
 * If maximum input length is exceeded, input will be trimmed,
 * and the user will be notified.
 */

#define MAX_LINE_LENGTH 50 // most terminal screens are longer than this
#define MAX_INPUT 200

struct termios orig_termios; // struct to save original terminal settings

struct Input_handler {
  int previous_space;
  char *input;
  int lines;
  int chars;
};

struct Space_holder {
  int previous_space;
};

void disable_raw_mode() {
  /* Restore original terminal settings. */
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
  /* Turn off canononical mode in terminal
   * so that keystrokes are sent to the program. */

  // Save original terminal settings
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disable_raw_mode); // ensure settings are restored

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON); // Stop terminal from processing input

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

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

void insert_newline(char *input, struct Space_holder *last_space) {
  /* A newline will be inserted at a space as close to
   * MAX_LINE_LENGTH as possible. */
  int line_end = MAX_LINE_LENGTH;

  line_end = find_space(input, last_space->previous_space);
  input[line_end] = '\n';
  last_space->previous_space = line_end + MAX_LINE_LENGTH;
}

int handle_backspace(char *input, int chars) {
  if (chars == 0) // prevents writing to illegal index of input[]
    return chars;
  chars--;
  input[chars] = 0;
  printf("\033[1D \033[1D"); // overwrite character and move cursor back
  return chars;
}

int handle_input(char *input) {
  enable_raw_mode();

  int c, chars, lines;
  int carriage_return_size = 10;

  char *carriage_return = malloc(carriage_return_size); // room for escape characters
  memset(carriage_return, 0, carriage_return_size);
  carriage_return[0] = '\r';

  struct Space_holder *last_space = malloc(sizeof(struct Space_holder));
  last_space->previous_space = MAX_LINE_LENGTH;

  chars = lines = 0;

  while ((c = getchar()) != '\n') {
    if (chars >= MAX_INPUT - 1) {
      printf("\nCharacter limit has been exceeded. Your input will not be saved.\n");
      goto error;
    }

    if (c == 127) {
      chars = handle_backspace(input, chars); // chars value must be updated
    } else {
      input[chars] = c; // append new character to input
      chars++; // increment chars now so that count is accurate
    }

    if (chars - (MAX_LINE_LENGTH * lines) > MAX_LINE_LENGTH) {
      insert_newline(input, last_space);
      lines++;
      printf("\33[2K\n"); // erase left over word fragments and jump to newline
      /* carriage_return variable must return to original cursor position
      * every time a newline is printed. */
      snprintf(carriage_return, carriage_return_size, "\033[%dA\r", lines);
      fflush(stdout);
    }

    printf("%schars % 2d/%03d %s", carriage_return, chars, MAX_INPUT, input); // reprint input, overwriting current input
    fflush(stdout);
  }
  printf("\n");

  free(carriage_return);
  free(last_space);
  return 0;
  
 error:
  free(carriage_return);
  free(last_space);
  return 1;
}

int main(int argc, char *argv[]) {
  /** User input is initialised in main function
   * so that it can be available from here.
   */
  char *input = malloc(MAX_INPUT);
  memset(input, 0, MAX_INPUT);

  printf("Please type your text below. Limit is %d\n", MAX_INPUT);
  int rc = handle_input(input);
  if (rc != 0)
    goto error;
  
  free(input);
  return 0;

 error:
  free(input);
  return 1;
}
