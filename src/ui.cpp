#include "../hdr/ui.hpp"
#include <ncurses.h>

#define COLOR_ORANGE                                                           \
  14 // random large enough number so it doesn't collide with any other color

void INIT_NCURSES() {
  initscr();
  cbreak(); // Disable line buffering
  noecho(); // Disable echoing of characters
  curs_set(
      0); // Set cursor visibility (0: invisible, 1: normal, 2: very visible)
  nodelay(stdscr, TRUE); // Enable non-blocking input
  timeout(0);            // Set getch to return immediately if there's no input
  keypad(stdscr, true);
  start_color();
  use_default_colors();
  init_color(COLOR_ORANGE, 1000, 500, 0);
  init_pair(blue, COLOR_BLUE, 0);
  init_pair(cyan, COLOR_CYAN, 0);
  init_pair(green, COLOR_GREEN, 0);
  init_pair(red, COLOR_RED, 0);
  init_pair(yellow, COLOR_YELLOW, 0);
  init_pair(magenta, COLOR_MAGENTA, 0);
  init_pair(orange, COLOR_ORANGE, 0);
}