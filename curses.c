#include <curses.h>
#include <unistd.h>

const char * s = "HELLO";

enum { delay_second = 5 };

int main(void) {

  int row, col;

  initscr(); /* initialized library */
  getmaxyx(stdscr, row, col); /* get size screen */

  move(row / 2, (col - sizeof(s) - 1) / 2); /* moving cursor */
  addstr(s); /* print string */
  curs_set(0); /* enter data */
  refresh(); /* show data */

  sleep(delay_second); /* sleep 5 sec */

  endwin(); /* close work with library */

  return 0;
}
