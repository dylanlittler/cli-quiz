#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raw_mode.h"

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

struct Input_handler {
  int max_line_length;
  int max_input;
  int previous_space;
  char *input;
  int lines;
  int chars;
  int cursor_pos;
  char *carriage_return;
  int carriage_return_size;
  char *new_lines;
};

struct Line_break_stack {
  int *line_breaks;
  int last_lb;
};

// forward declarations
struct Input_handler *Input_handler_init(int max_line_length, int max_input);

struct Line_break_stack *Line_break_stack_init(struct Input_handler *input);

void close_input_handler(struct Input_handler *input_handler);
void close_line_break_stack(struct Line_break_stack *lbs);

  
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

void handle_backspace(struct Input_handler *input, struct Line_break_stack *lbs) {
  if (input->chars == 0) // prevents writing to illegal index of input[]
    return;
  input->chars--;
  input->cursor_pos--;
  if (input->input[input->chars] == '\n') {
    printf("\033[0A");
    lbs->last_lb--;
    input->cursor_pos = lbs->line_breaks[lbs->last_lb] + 1;
    if (input->chars <= input->max_line_length) {
      memset(input->carriage_return, 0, input->carriage_return_size);
      input->carriage_return[0] = '\r';
      memset(input->new_lines, 0, input->carriage_return_size);
    }
    printf("\033[%dC\033[1D \033[1D", input->cursor_pos);
  } else {
    printf("\033[1D \033[1D"); // overwrite character and move cursor back
  }
  input->input[input->chars] = 0;
}

void increment_last_lb(struct Line_break_stack *lbs, struct Input_handler *input) {
  if (lbs->last_lb > 0) {
  lbs->line_breaks[lbs->last_lb] = input->previous_space - lbs->line_breaks[lbs->last_lb - 1];
  } else {
    lbs->line_breaks[lbs->last_lb] = input->previous_space;
  }
  lbs->last_lb++;
}

char *handle_input(int max_line_length, int max_input) {
  enable_raw_mode();

  struct Input_handler *ih = Input_handler_init(max_line_length, max_input);

  struct Line_break_stack *lbs = Line_break_stack_init(ih);
  
  int c, i;
  int char_display = 0;
  int trailing_chars = 0;

  printf("\033[s");
  printf("chars    0/%d ", ih->max_input);
  while ((c = getchar()) != '\n') {
    if (ih->chars >= ih->max_input - 1) {
      printf("\nCharacter limit has been exceeded. Your input will not be saved.\n");
      goto error;
    }

    if (c == 127) {
      handle_backspace(ih, lbs);
      char_display--;
    } else {
      ih->input[ih->chars] = c; // append new character to input
      char_display = ih->chars + 1;
    }

    if (ih->chars - 1 - (ih->max_line_length * ih->lines) > ih->max_line_length) {
      ih->previous_space = find_space(ih);
      ih->input[ih->previous_space] = '\n';
      
      ih->lines++;
      increment_last_lb(lbs, ih);
      trailing_chars = (ih->max_line_length * (ih->lines)) - ih->previous_space;
      printf("\033[%dD", trailing_chars + 1);
      for (i = 0; i <= trailing_chars; i++) {
	printf(" ");
      }
      printf("\n"); // erase left over word fragments and jump to newline
      for (i = trailing_chars; i >= 0; i--) {
	printf("%c", ih->input[(ih->max_line_length * ih->lines) + 1 - i]);
      }
      /* carriage_return variable must return to original cursor position
      * every time a newline is printed. */
      snprintf(ih->carriage_return, ih->carriage_return_size, "\033[%dA\r", ih->lines);
      snprintf(ih->new_lines, ih->carriage_return_size, "\033[%dB\r", ih->lines);
      fflush(stdout);
      ih->cursor_pos = trailing_chars + 1;
      ih->previous_space += ih->max_line_length;
    }

    printf("\033[u\033[s\033[6C% 4d/%d%s\033[%dC%c", char_display,
	   ih->max_input, ih->new_lines, ih->cursor_pos, ih->input[ih->chars]);

    if (c != 127) {
      ih->chars++;
      ih->cursor_pos++;
    }
    fflush(stdout);
  }
  printf("\n");

  char *user_input = malloc(max_input);
  memcpy(user_input, ih->input, max_input);
  close_input_handler(ih);
  close_line_break_stack(lbs);
  return user_input;

 error:
  close_input_handler(ih);
  close_line_break_stack(lbs);
  return "";
}

struct Input_handler *Input_handler_init(int max_line_length, int max_input) {
  /* Initialise Input_handler struct. */
  int cr_size = 10;
  struct Input_handler *ih = malloc(max_input + (sizeof(int) * 7) + cr_size); // add checks
  ih->input = malloc(max_input);
  memset(ih->input, 0, max_input);
  ih->max_line_length = max_line_length;
  ih->max_input = max_input;
  ih->previous_space = max_line_length;
  ih->lines = ih->chars = 0;
  ih->cursor_pos = 1;
  ih->carriage_return_size = cr_size;
  ih->carriage_return = malloc(cr_size);
  memset(ih->carriage_return, 0, cr_size);
  ih->carriage_return[0] = '\r';
  ih->new_lines = malloc(cr_size);
  memset(ih->new_lines, 0, cr_size);
  return ih;
}

struct Line_break_stack *Line_break_stack_init(struct Input_handler *input) {
  struct Line_break_stack *lbs = malloc(sizeof(int) * (input->max_input / input->max_line_length + 1));
  lbs->line_breaks = malloc((input->max_input / input->max_line_length + 1) * sizeof(int));
  memset(lbs->line_breaks, 0, input->max_input / input->max_line_length + 1);
  lbs->last_lb = 0;
  return lbs;
}

void close_input_handler(struct Input_handler *input_handler) {
  if (input_handler) {
    if (input_handler->input)
      free(input_handler->input);
    if (input_handler->carriage_return)
      free(input_handler->carriage_return);
    if (input_handler->new_lines)
      free(input_handler->new_lines);
    free(input_handler);
  }
}

void close_line_break_stack(struct Line_break_stack *lbs) {
  if (lbs) {
    if (lbs->line_breaks)
      free(lbs->line_breaks);
    free(lbs);
  }
}

int main(int argc, char *argv[]) {
  /** User input is initialised in main function
   * so that it can be available from here.
   */
  int max_line_length, max_input;
  if (argc == 3) {
    max_line_length = atoi(argv[1]);
    max_input = atoi(argv[2]);
  } else {
    max_line_length = 50;
    max_input = 200;
  }

  //char *user_input = malloc(max_input);
  //memset(user_input, 0, max_input);
  
  printf("Please type your text below. Limit is %d\n", max_input);
  char *user_input = handle_input(max_line_length, max_input);
  printf("%s\n", user_input);
  free(user_input);
  return 0;
}
