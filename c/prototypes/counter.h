#ifndef _counter_h_
#define _counter_h_

// define structs and functions which will be accessed by counter_main
struct Input_handler {
  int max_line_length;
  int max_input;
  int previous_space;
  char *input;
  int lines;
  int chars;
};

int handle_input(struct Input_handler *input);

struct Input_handler *Input_handler_init(int max_line_length, int max_input);

void close_input_handler(struct Input_handler *input_handler);

#endif
