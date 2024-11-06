#include <stdio.h>
#include "printf.c"

static char *StrPad(int *len, const char *str, char c, int count)
{
	int outLen = 0;
	char *outStr = NULL;
	const bool leftpad = count < 0;
	int i;

	if (!str) str = "";
	else outLen = strlen(str);

	/* it's actually better to force the count to be negative because
	 * negative INT_MAX is a valid int (assuming 2's compliment) 
	 * but negative INT_MIN (which is a positive number) doesn't
	 * fit in an int (again, assuming 2's compliment) */
	count = (count > 0)? -count : count;

	outStr = calloc(sizeof(char), outLen - count + 1 /* null byte */);
	if (!outStr) {
		if (len) *len = 0;
		return NULL;
	}

	for (i = 0; i > count; --i) {
		if (leftpad) {
			outStr[-i] = c;
			continue;
		}

		outStr[-i + outLen] = c;
	}

	if (leftpad) memcpy(outStr - i, str, outLen);
	else memcpy(outStr, str, outLen);

	outLen -= i;
	if (len) *len = outLen;

	return outStr;
}

int main(void)
{
	int len = 0;
	char *padded = StrPad(&len, NULL, 'a', 100);
	printf("len = %d;\n%s\n", len, padded);
	free(padded);

	return 0;
}
