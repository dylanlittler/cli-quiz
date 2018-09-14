#include <stdio.h>
#include <stdlib.h>

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

  struct Input_handler *input = Input_handler_init(max_line_length, max_input);

  printf("Please type your text below. Limit is %d\n", input->max_input);
  int rc = handle_input(input);
  if (rc != 0)
    goto error;
  
  close_input_handler(input);
  return 0;

 error:
  close_input_handler(input);
  return 1;
}
