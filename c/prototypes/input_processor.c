#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstrlib.h"
#include "raw_mode.h"

/**
 * This program clears the screen, receives live input from user,
 * displays a character count, and drops to a newline whenever
 * max_line_length has been exceeded.
 * User input with newlines inserted will be returned to the
 * calling function.
 */


// forward declarations
struct Input_handler *Input_handler_init(int max_line_length);

void close_input_handler(struct Input_handler *input_handler);

struct Input_handler {
  int max_line_length; // length before line break
  int previous_space; // last space before word that crosses line break
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

void Expand_String(struct Input_handler *ih, int new_size) {
  ih->input = realloc(ih->input, new_size);
}

bstring handle_input(int max_line_length) {
  enable_raw_mode();
  clear_screen();

  struct Input_handler *ih = Input_handler_init(max_line_length);
  check(ih != NULL, "Input handler not allocated correctly.");
  int c;
  
  printf("Screen cleared to allow room for input.\n");
  printf("Please type your input below.\n");
  printf("\033[s");
  printf("chars % 4d ", ih->chars);
  
  while ((c = getchar()) != '\n') {

    if (c == 127) {
      handle_backspace(ih);
    } else {
      ih->input[ih->chars] = c; // append new character to input
      ih->chars++; // increment chars now so that count is accurate
    }

    if (ih->chars - (ih->max_line_length * ih->lines) >= ih->max_line_length) {
      ih->lines++;
      Expand_String(ih, (ih->lines + 1) * ih->max_line_length);
      ih->input[ih->chars] = '\0'; // Null byte is not set after reallocation.
      ih->previous_space = find_space(ih);
      ih->input[ih->previous_space] = '\n';
      ih->previous_space += ih->max_line_length;

      printf("\33[2K\n"); // erase left over word fragments and jump to newline
      fflush(stdout);
    }
    ih->input[ih->chars] = '\0';
    printf("%schars % 4d %s", "\033[u\033[s", ih->chars, ih->input); // reprint input, overwriting current input
    fflush(stdout);
  }
  printf("\n");

  //char *user_input = malloc((ih->lines + 1) * ih->max_line_length);
  //memcpy(user_input, ih->input, (ih->lines + 1) * ih->max_line_length);
  bstring user_input = bfromcstr(ih->input);
  close_input_handler(ih);
  return user_input;

 error:
  return NULL;
}

struct Input_handler *Input_handler_init(int max_line_length) {
  /* Initialise Input_handler struct. */
  struct Input_handler *ih = malloc(sizeof(char *) + (sizeof(int) * 4));
  check_mem(ih);
  ih->input = malloc(max_line_length);
  check_mem(ih->input);
  ih->max_line_length = max_line_length;
  ih->previous_space = max_line_length;
  ih->lines = ih->chars = 0;
  return ih;

 error:
  return NULL;
}

void close_input_handler(struct Input_handler *input_handler) {
  if (input_handler) {
    if (input_handler->input)
      free(input_handler->input);
    free(input_handler);
  }
}
