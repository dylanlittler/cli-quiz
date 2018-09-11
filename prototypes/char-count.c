#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program will provide a live character count of
 * the user's input by adding each character to a variable
 * and printing out from the start of the line.
 * Terminal settings must be changed to achieve this,
 * as characters will otherwise not be received by the program
 * until the user hits enter.
 */

struct termius orig_termios;

void enable_raw_mode();

void disable_raw_mode();

int main(int argc, char *argv[]);
