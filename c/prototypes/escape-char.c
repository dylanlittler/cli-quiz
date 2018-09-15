#include <stdio.h>
#include <unistd.h>

/* This program is designed to test passing escape characters in a variable.
 * The carriage end test does return to the previous line,
 * but multiple returns will not go beyond that, due to the fact that previous
 * output has been written to stdout. Raw mode may be required
 * to achieve this, and the output would need to be sent all at once
 * from a struct.
 */

int main(int argc, char *argv[]) {
  /* This code is no longer relevant. Saving cursor position now to be attempted. */
  /*char newline = '\n';
  char *newlines = "\n\n\n";
  char tab = '\t';
  char *tabs = "\t\t\t";
  char carriage_return = '\r';
  char *carriage_returns = "\r\r\r";

  printf("Single newline character: %cEND\n", newline);
  printf("Newline characters string pointer: %sEND\n", newlines);
  printf("Single tab: %cEND\n", tab);
  printf("Multiple tabs: %sEND\n", tabs);
  printf("Warning: unexepected results may occur from carriage returns after this point.\n");
  printf("Single carriage return: %cCARRIAGE_END\n", carriage_return);
  printf("Multiple carriage returns: %sCARRIAGES_END\n", carriage_returns);*/

  // Ensure that newline is printed afterwards

  /* These codes may not work on this terminal emulator. */
  printf("\033[s"); // save cursor position
  printf("Original position.");
  fflush(stdout);
  sleep(1);
  printf("\033[5A"); // move cursor down five lines
  printf("I am here now after dropping down five lines.");
  fflush(stdout);
  sleep(1);
  printf("\033[u"); // restore original cursor position
  printf("I am back here now.");
  fflush(stdout);
  printf("\n");

  return 0;
}
