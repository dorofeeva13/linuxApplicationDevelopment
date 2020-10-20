#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#ifdef WITHOUT_UTF
#define PCRE_OPTIONS 0
#else
#define PCRE_OPTIONS PCRE2_UCP
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

	int errnum, i, rc;

	initscr();
	cbreak();
	printw("Input:");
	refresh();
	int half = (COLS - 2 * DX) / 2;

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

		wprintw(winLOG, " \'%s\': \'%s\'\n", inRE, inSTR);

	  PCRE2_SPTR pattern = (PCRE2_SPTR)inRE;
	  PCRE2_SPTR subject = (PCRE2_SPTR)inSTR; 

	  PCRE2_SIZE erroffs;
	  PCRE2_SIZE *ovector;
	  PCRE2_SIZE subject_length = (PCRE2_SIZE)strlen((char *)subject);

    pcre2_code *re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE_OPTIONS, &errnum, &erroffs, NULL);

    if (re == NULL) {
      PCRE2_UCHAR buffer[256];
      pcre2_get_error_message(errnum, buffer, sizeof(buffer));
      wprintw(winLOG, "PCRE2 compilation failed at offset %d: %s\n", (int)erroffs, buffer);
    }

    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
      switch(rc) {
      case PCRE2_ERROR_NOMATCH:
        wprintw(winLOG, "	No match\n");
        break;
      default:
        wprintw(winLOG, "	Matching error %d\n", rc);
        break;
      }
    }

    ovector = pcre2_get_ovector_pointer(match_data);

    for (i = 0; i < rc; i++) {
      wprintw(winLOG, "  %2ld: %.*s\n", ovector[2*i], (int)(ovector[2*i+1] - ovector[2*i]), subject + ovector[2*i]);
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);

    box(winLOG, 0, 0);
    wrefresh(winLOG);
	} while (*inRE);

	endwin();
  
  return 0;
}