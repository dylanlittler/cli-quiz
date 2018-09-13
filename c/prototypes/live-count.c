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

char *insert_newline(char *input) {
  /* A newline will be inserted at a space at intervals as close to
   * MAX_LINE_LENGTH as possible. Iteration will continue as long
   * as the remaining string exceeds this limit.
   */

  int line_end = MAX_LINE_LENGTH;
  int line_start = 0;
  int prev_line_end = 0;

  for (line_start = 0; line_start <= strlen(input); line_start += MAX_LINE_LENGTH) {
    if (strlen(input) - line_start <= MAX_LINE_LENGTH) {
      return input; // break the loop if inserting newline is not needed
    } else {
      line_end = find_space(input, prev_line_end, line_end);
      input[line_end] = '\n';
      prev_line_end = line_end; // save previous end point to be used as starting point for find_space()
      line_end += MAX_LINE_LENGTH;
    }
  }
  return input;
}


int main(int argc, char *argv[]) {
  enable_raw_mode();

  int c, chars, lines;

  int return_size = 10;
  char *carriage_return = malloc(return_size); // escape characters required should not exceed 10 characters
  memset(carriage_return, 0, return_size);
  carriage_return[0] = '\r';
  
  char *input = malloc(MAX_INPUT);
  memset(input, 0, MAX_INPUT);

  chars = 0;
  lines = 0;
  printf("Please type your text below. Limit is %d\n", MAX_INPUT);
  while ((c = getchar()) != '\n') {
    if (chars >= MAX_INPUT - 1) { // ensure that memory limit will not be exceeded
      printf("\nCharacter limit has been exceeded. Your input will not be saved.\n");
      free(input); // free variable if program is forced to abort
      exit(1);
    }

    if (c == 127) { // handle backspace
      if (chars == 0) //prevents errors caused by initial backspace
	continue;
      chars--;
      input[chars] = 0;
      printf("\033[1D \033[1D"); // erase character and move cursor back
    } else {
      input[chars] = c; //append new character to input
      chars++; // increment now so that count will be accurate
    }
    
    if (chars - (MAX_LINE_LENGTH * lines) > MAX_LINE_LENGTH) {
      insert_newline(input);
      lines++;
      snprintf(carriage_return, return_size, "\033[%dA", lines - 1);
    }
    
    printf("%schars %03d/%03d %s", carriage_return, chars, MAX_INPUT, input); // reprint input, overwriting current input
  }
  printf("\n");

  free(input); // free input variable if program runs successfully
  free(carriage_return);
  
  return 0;
}
