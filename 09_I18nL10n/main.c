#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libintl.h>
#include <locale.h>

int main() {
	int left = 1, right = 100;
	printf("Make a number from 1 to 100\n");
	while (left < right) {
		int middle = (right + left) / 2;
		char ans[10];
		printf("Is your number bigger than %d ?\n", middle);
		printf("If yes - write 'y', else -'n':\n");
		scanf("%8s", ans);
		if (strlen(ans) > 1 || !(ans[0] == 'y') || !(ans[0] == 'n')) {
			printf("Wrong answer, please try again!\n");
			continue;
		} else if (ans[0] == 'y') {
			left = middle + 1;
			continue;
		} else {
			right = middle;
			continue;
		}
	}
	printf("Wished number is %d\n", left);
	return 0;
}