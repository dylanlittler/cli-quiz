#ifndef _input_processor_h_
#define _input_processor_h_

/** This header includes two c files and provides
 * definitions to make their functions accessible
 * to other programs.
 */

void enable_raw_mode();
void disable_raw_mode();
void count_characters(char *input, int max_input);

void insert_newlines(char *input, int max_length);
int find_space();

#endif
