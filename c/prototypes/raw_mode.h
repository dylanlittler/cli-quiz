#ifndef _raw_mode_h_
#define _raw_mode_h_

/* This header provides a function to put the terminal into raw mode
 * for the duration of the calling program's execution.
 * A function for clearing the screen is also provided. */

void enable_raw_mode();

void clear_screen();

#endif
