#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

/* This program contains functions for setting terminal
 * to raw mode for the duration of execution and for
 * clearing the screen. */

void clear_screen() {
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

struct termios orig_termios; // save original terminal settings

void disable_raw_mode() {
  /* Restore original terminal settings. */
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
  /* Turn off canonical mode in terminal so that
   * keystrokes are sent to the program. */

  // save original terminal settings
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disable_raw_mode); // ensure settings are restored even in case of interrupt

  struct termios raw = orig_termios; // copy settings to modify
  raw.c_lflag &= ~(ECHO | ICANON);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
