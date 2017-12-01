// Roguelike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "curses.h"

int main() {
	initscr();										 /* Initialize screenbuffer */
	
	if (has_colors) {								 /* If console has colors */
		start_color();								 /* Initialize colors*/
		init_pair(1, COLOR_BLACK, COLOR_BLACK);      /* Example of block with black text and bg */
	}		
	
	resize_term(30, 70);							 /* Resizes screenbuffer size of 30 y 70 x */

	refresh();
	getch();
	endwin();
	return 0;
}