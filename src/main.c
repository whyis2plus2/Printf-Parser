#include <stdio.h>
#include "printf.c"

int main(void)
{
	printf("%0-6.4sa\n", "tests");
	return 0;
}
