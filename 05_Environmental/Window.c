#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#define DX 3
#define ONLELINE 3
#define MAXSTR 80

#include <stdio.h>
#include <ncurses.h>
#include <pcre2.h>
#include <string.h>

int main(int argc, char **argv)
{
  WINDOW *winRE, *winSTR, *winLOG;

  char inRE[MAXSTR], inSTR[MAXSTR];

	int half = (COLS - 2 * DX) / 2;
	int errnum, i, rc;

	pcre2_code *re;
  PCRE2_SPTR pattern;
  PCRE2_SPTR subject;

  PCRE2_SIZE erroffs;
  PCRE2_SIZE *ovector;
  PCRE2_SIZE subject_length;
  pcre2_match_data *match_data;

	initscr();
	cbreak();
	printw("Input:");

	winRE = newwin(ONLELINE, half, DX, DX);
	winSTR = newwin(ONLELINE, half, DX, DX + half);
	winLOG = newwin(LINES - ONLELINE - DX * 2, COLS - 2 * DX, DX + ONLELINE, DX);

	keypad(winRE, TRUE);
	keypad(winSTR, TRUE);
	scrollok(winLOG, TRUE);

	do {
		werase(winRE);
		box(winRE, 0, 0);
		mvwgetnstr(winRE, 1, 1, inRE, MAXSTR);
		werase(winSTR);
		box(winSTR, 0, 0);
		mvwgetnstr(winSTR, 1, 1, inSTR, MAXSTR);

    //to be done
	} while (*inRE);

	endwin();
  
  return 0;
}