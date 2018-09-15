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

struct termios orig_termios; // struct to save original terminal settings

struct Input_handler {
  int max_line_length;
  int max_input;
  int previous_space;
  char *input;
  int lines;
  int chars;
  char *carriage_return;
  int carriage_return_size;
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

int find_space(struct Input_handler *input) {
  /* Search for spaces in input before end
   * and return the number of the index. */
  int i = 0;
  for (i = 0; i < input->max_line_length; i++) {
    if (input->input[input->previous_space - i] == ' ')
      return input->previous_space - i;
  }
  return input->previous_space; // fallthrough in case string contains no spaces
}

void insert_newline(struct Input_handler *input) {
  /* A newline will be inserted at a space as close to
   * MAX_LINE_LENGTH as possible. */

  input->previous_space = find_space(input);
  input->input[input->previous_space] = '\n';
  input->previous_space += input->max_line_length;
}

void handle_backspace(struct Input_handler *input) {
  if (input->chars == 0) // prevents writing to illegal index of input[]
    return;
  input->chars--;
  if (input->input[input->chars] == '\n') {
    printf("\033[0A");
    input->lines--;
    if (input->lines == 0) {
      memset(input->carriage_return, 0, input->carriage_return_size);
      input->carriage_return[0] = '\r';
    } else {
      snprintf(input->carriage_return, input->carriage_return_size, "\033[%dA\r", input->lines);
    }
    input->input[input->chars] = 0;

  } else {

    input->input[input->chars] = 0;
  }
  printf("\033[1D \033[1D"); // overwrite character and move cursor back
}

int handle_input(struct Input_handler *ih) {
  enable_raw_mode();

  int c;
  printf("\033[s");
  printf("chars % 4d/%03d ", ih->chars, ih->max_input);
  while ((c = getchar()) != '\n') {
    if (ih->chars >= ih->max_input - 1) {
      printf("\nCharacter limit has been exceeded. Your input will not be saved.\n");
      goto error;
    }

    if (c == 127) {
      handle_backspace(ih);
    } else {
      ih->input[ih->chars] = c; // append new character to input
      ih->chars++; // increment chars now so that count is accurate
    }

    if (ih->chars - (ih->max_line_length * ih->lines) >= ih->max_line_length) {
      //insert_newline(input);
      ih->lines++;
      ih->previous_space = find_space(ih);
      ih->input[ih->previous_space] = '\n';
      ih->previous_space += ih->max_line_length;

      //printf("\33[2K\n"); // erase left over word fragments and jump to newline
      //printf("\n");
      /* carriage_return variable must return to original cursor position
      * every time a newline is printed. */
      //snprintf(ih->carriage_return, ih->carriage_return_size, "\033[%dA\r", ih->lines);

      fflush(stdout);
    }
    
    printf("%schars % 4d/%03d %s", "\033[u\033[s", ih->chars, ih->max_input, ih->input); // reprint input, overwriting current input
    fflush(stdout);
  }
  printf("\n");

  return 0;
  
 error:
  return 1;
}

struct Input_handler *Input_handler_init(int max_line_length, int max_input) {
  /* Initialise Input_handler struct. */
  int cr_size = 10;
  struct Input_handler *ih = malloc(max_input + sizeof(int) * 6 + cr_size); // add checks
  ih->input = malloc(max_input);
  memset(ih->input, 0, max_input);
  ih->max_line_length = max_line_length;
  ih->max_input = max_input;
  ih->previous_space = max_line_length;
  ih->lines = ih->chars = 0;
  ih->carriage_return_size = cr_size;
  ih->carriage_return = malloc(cr_size);
  memset(ih->carriage_return, 0, cr_size);
  ih->carriage_return[0] = '\r';
  return ih;
}

void close_input_handler(struct Input_handler *input_handler) {
  if (input_handler) {
    if (input_handler->input)
      free(input_handler->input);
    if (input_handler->carriage_return)
      free(input_handler->carriage_return);
    free(input_handler);
  }
}
