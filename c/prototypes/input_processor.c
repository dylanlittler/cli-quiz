#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raw_mode.h"

/**
 * This program clears the screen, receives live input from user,
 * displays a character count, and drops to a newline whenever
 * max_line_length has been exceeded.
 * User input with newlines inserted will be returned to the
 * calling function.
 */


// forward declarations
struct Input_handler *Input_handler_init(int max_line_length, int max_input);

void close_input_handler(struct Input_handler *input_handler);

struct Input_handler {
  int max_line_length;
  int max_input;
  int previous_space;
  char *input;
  int chars;
  int lines;
};

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

void handle_backspace(struct Input_handler *input) {
  if (input->chars == 0) // prevents writing to illegal index of input[]
    return;
  input->chars--;
  if (input->input[input->chars] == '\n') {
    input->lines--; // undo what is done when newline is inserted
    input->previous_space -= input->max_line_length;
  }
  input->input[input->chars] = 0;
  printf("\033[1D \033[1D"); // overwrite character and move cursor back
}

char *handle_input(int max_line_length, int max_input) {
  enable_raw_mode();
  clear_screen();

  struct Input_handler *ih = Input_handler_init(max_line_length, max_input);
  
  int c;
  
  printf("Screen cleared to allow room for input.\n");
  printf("Please type your input below. Limit is %d characters.\n", max_input);
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
      ih->lines++;
      ih->previous_space = find_space(ih);
      ih->input[ih->previous_space] = '\n';
      ih->previous_space += ih->max_line_length;

      printf("\33[2K\n"); // erase left over word fragments and jump to newline
      fflush(stdout);
    }
    
    printf("%schars % 4d/%03d %s", "\033[u\033[s", ih->chars, ih->max_input, ih->input); // reprint input, overwriting current input
    fflush(stdout);
  }
  printf("\n");

  char *user_input = malloc(max_input);
  memcpy(user_input, ih->input, ih->max_input);
  close_input_handler(ih);
  return user_input;
  
 error:
  close_input_handler(ih);
  user_input = NULL; // main function will check for this
  return user_input;
}

struct Input_handler *Input_handler_init(int max_line_length, int max_input) {
  /* Initialise Input_handler struct. */
  struct Input_handler *ih = malloc(max_input + sizeof(int) * 5); // add checks
  ih->input = malloc(max_input);
  memset(ih->input, 0, max_input);
  ih->max_line_length = max_line_length;
  ih->max_input = max_input;
  ih->previous_space = max_line_length;
  ih->lines = ih->chars = 0;
  return ih;
}

void close_input_handler(struct Input_handler *input_handler) {
  if (input_handler) {
    if (input_handler->input)
      free(input_handler->input);
    free(input_handler);
  }
}
