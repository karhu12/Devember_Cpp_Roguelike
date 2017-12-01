#include "stdafx.h"
#include "curses.h"

int main() {
	initscr();										/* Start curses */
	resize_term(23, 56);							/* Set initial window size */
	WINDOW *status,*game, *textBar, *gameBox;		/* Initialize 3 windows for status,text and game */
	status = newwin(20, 15, 3, 0);
	game = newwin(20, 40, 3, 16);
	textBar = newwin(3, 55, 0, 0);					/* new window with size = (Columns, Rows, start y, start x) */
	
	do {
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 39; j++)
				mvwaddch(game, i, j, '.');
		}
		mvwprintw(textBar, 1, 1, "Text bar > ");
		mvwprintw(status, 1, 1, "Status bar");
		box(status, '|', '-');
		box(textBar, '|', '-');						/* read stuff to window buffers */
		wrefresh(game);								/* Refresh draws buffer to actual screen */
		wrefresh(status);
	} while (wgetch(textBar));						/* wgetch also refreshes selected window */
	
	delwin(status);
	delwin(game);
	delwin(textBar);
	endwin();										/* Delete window buffer memories */

	return 0;
}