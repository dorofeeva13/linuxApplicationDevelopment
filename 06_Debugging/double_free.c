#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int n = 10;
	char *str = malloc(n);
	fgets(str, n, stdin);
	fprintf(stdout, "%s\n", str);
	free(str);
	free(str);
	return 0;
}