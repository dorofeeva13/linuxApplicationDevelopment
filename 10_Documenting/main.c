#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

#define HELP _("\
program can guess the number you make.\n\
\n\
Usage: ./main [CONFIG]...\n\
\n\
Configuration:\n\
--help                  show help info\n\
-r                      enable roman numbers\n")

static char* ROMAN[100] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

char* arabicToRoman(int num) {
    if (num > 100 || num < 1) {
        return NULL;
    }
    return ROMAN[num - 1];
}

int arabicFromRoman(char* num) {
    for (int i = 1; i < 101; i++) {
        if (strcmp(ROMAN[i - 1], num) == 0) {
            return i;
        }
    }
    return -1;
}

char* numberToString(int num, int roman) {
	if (roman == 1) {
		return arabicToRoman(num);
	} else {
		char* str = (char *)malloc(sizeof(char) * 4);
		sprintf(str, "%d", num);
		return str;
	}
}

int main(int argc, char **argv) {
	int left = 1, right = 100;
	setlocale (LC_ALL, "");
	bindtextdomain ("main", ".");
  textdomain("main");
  int roman = 0;
  if (argc > 1 && strcmp("-r", argv[1]) == 0) {
  	roman = 1;
  } else if (argc > 1 && strcmp("--help", argv[1]) == 0) {
  	printf("%s\n", HELP);
  	return 0;
  } else if (argc > 1 && strcmp("--version", argv[1]) == 0) {
  	printf("%s\n", "0.0");
  	return 0;
  }
	printf("Make a number from %s to %s\n", numberToString(1, roman), numberToString(100, roman));
	while (left < right) {
		int middle = (right + left) / 2;
		char ans[10];
		printf("Is your number bigger than %s ?\n", numberToString(middle, roman));
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
	printf("Wished number is %s\n", numberToString(left, roman));
	return 0;
}