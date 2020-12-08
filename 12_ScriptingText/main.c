#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main() {
	int left = 1, right = 100;
	setlocale (LC_ALL, "");
	bindtextdomain ("main", ".");
  textdomain("main");
	printf("Make a number from 1 to 100\n");
	while (left < right) {
		int middle = (right + left) / 2;
		char ans[10];
		printf("Is your number bigger than %d ?\n", middle);
		printf("If yes - write 'y', else -'n':\n");
		scanf("%8s", ans);
		if (strcmp(ans, _("y"))) {
			left = middle + 1;
			continue;
		} else if (strcmp(ans, _("n"))) {
			right = middle;
			continue;
		} else {
			printf("Wrong answer, please try again!\n");
			continue;
		}
	}
	printf("Wished number is %d\n", left);
	return 0;
}