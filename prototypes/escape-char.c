#include <stdio.h>

/* This program is designed to test passing escape characters in a variable.
 * The carriage end test does return to the previous line,
 * but multiple returns will not go beyond that, due to the fact that previous
 * output has been written to stdout. Raw mode may be required
 * to achieve this, and the output would need to be sent all at once
 * from a struct.
 */

int main(int argc, char *argv[]) {
  char newline = '\n';
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
  printf("Multiple carriage returns: %sCARRIAGES_END\n", carriage_returns);

  // Ensure that newline is printed afterwards
  printf("\n");

  return 0;
}
