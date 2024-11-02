#include "printf.h"

#include <string.h> /* strlen */

/* A struct that holds all formatting data for one format specifier */
typedef struct FormatData {
	bool leftAlign: 1; /* - */
	bool visibleSign: 1; /* + */
	bool prependZero: 1; /* 0 */
	bool altForm: 1; /* # */
	unsigned int width, precision;
} FormatData;

/* Convert a signed long to an ascii string stored in the buffer
 * this function returns the length of the resulting string
 * or -1 if an error occurs */
static int SLongToASCII(char buffer[65], long x, int radix, bool upper);

/* Convert an unsigned long to an ascii string stored in the buffer
 * this function returns the length of the resulting string
 * or -1 if an error occurs */
static int ULongToASCII(char buffer[65], unsigned long x, int radix, bool upper);

/* write x to the buffer, if the buffer has enough room
 * if the char was written successfully, this function returns true
 * otherwise, this function returns false */
static bool WriteChar(char *buff, int buffsz, int index, char x);

/* write x to the buffer if the buffer has enough room,
 * written copy of x gets truncated if there isn't enough room
 * this function returns the length of x + any padding */
static int WriteString(
	char *buff, int buffsz,
	int startIndex, const char *x,
	FormatData fmt
);

static int WriteSLong(
	char *buff, int buffsz, 
	int startIndex, long x, 
	int radix, bool upper, 
	FormatData fmt
);

static int WriteULong(
	char *buff, int buffsz,
	int startIndex, unsigned long x,
	int radix, bool upper,
	FormatData fmt
);

/* Convert a signed long to an ascii string stored in the buffer
 * this function returns the length of the resulting string
 * or -1 if an error occurs */
static int SLongToASCII(char buffer[65], long x, int radix, bool upper)
{
	int i, buffsz = 65;
	const bool negative = x < 0;

	/* the final length of the string */
	int len = 0;

	if (!buffer) return -1;
	if (radix < 2 || radix > 36) return -1;

	/* make the buffer ignore the first character for now */
	if (negative) { ++buffer; --buffsz; }
	for (i = 0; i < buffsz; ++i) {
		int digit = x % radix;

		/* force digit to be a positive number so that it can be converted to the right char */
		if (digit < 0) digit = -digit;
		
		digit += (digit < 10)? '0' : 'a' - 10;

		/* convert letter digit to lowercase when specified */
		if (upper && digit >= 'a') digit -= 0x20;

		buffer[i] = digit;

		/* break out of the loop if x is 0 */
		if (x == 0) break;
		x /= radix;
	}

	/* give len the correct value */
	len = i;

	/* reverse the buffer so that the digits are in the right order */
	for (i = 0; i < len/2; ++i) {
		char tmp = buffer[i];

		/* len - 1 - i lets us index into the string in reverse order */
		buffer[i] = buffer[len - 1 - i];
		buffer[len - 1 - i] = tmp;
	}

	/* adjust the buffer back to normal if negative */
	if (negative) { --buffer; ++len; buffer[0] = '-'; }

	/* null terminate the buffer */
	buffer[len] = 0;

	return len;
}

/* Convert an unsigned long to an ascii string stored in the buffer
 * this function returns the length of the resulting string
 * or -1 if an error occurs */
static int ULongToASCII(char buffer[65], unsigned long x, int radix, bool upper)
{
	int i;

	/* the final length of the string */
	int len = 0;

	if (!buffer) return -1;
	if (radix < 2 || radix > 36) return -1;

	for (i = 0; i < 48; ++i) {
		int digit = x % radix;
		digit += (digit < 10)? '0' : 'a' - 10;

		/* convert letter digit to lowercase when specified */
		if (upper && digit >= 'a') digit -= 0x20;

		buffer[i] = digit;

		/* break out of the loop if x is 0 */
		if (x == 0) break;
		x /= radix;
	}

	/* give len the correct value */
	len = i;

	/* reverse the buffer so that the digits are in the right order */
	for (i = 0; i < len/2; ++i) {
		char tmp = buffer[i];

		/* len - 1 - i lets us index into the string in reverse order */
		buffer[i] = buffer[len - 1 - i];
		buffer[len - 1 - i] = tmp;
	}

	/* null terminate the buffer */
	buffer[len] = 0;

	return len;
}

/* write x to the buffer, if the buffer has enough room */
/* if the char was written successfully, this function returns true */
/* otherwise, this function returns false */
static bool WriteChar(char *buff, int buffsz, int index, char x)
{
	if (!buff) return false;
	if (index >= buffsz) return false;

	buff[index] = x;
	return true;
}

/* write x to the buffer, if the buffer has enough room, written copy of x gets */
/* truncated if there isn't enough room */
/* this function returns the length of x + any padding */
static int WriteString(
	char *buff, int buffsz,
	int startIndex, const char *x,
	FormatData fmt
)
{
	int i = 0;
	int ret = 0;
	int xLen = 0;
	bool needsPadding = fmt.width > xLen;

	if (!x) x = "<null>";
	xLen = strlen(x);

	/* pad so that the width is met */			
	if (needsPadding && !fmt.leftAlign) for (i = 0; i < fmt.width - xLen; ++i) {
		WriteChar(buff, buffsz, startIndex + i, fmt.prependZero? '0': ' ');
	}

	ret = xLen + i;

	/* iterate over every char in the string */
	for (i = 0; x[i] && i < fmt.precision; ++i) {
		WriteChar(
			buff,
			buffsz, 
			startIndex + i + (needsPadding && !fmt.leftAlign)
				?fmt.width - xLen
				:0,
			x[i]
		);
	}

	return i;
}

static int WriteSLong(
	char *buff, int buffsz, 
	int startIndex, long x, 
	int radix, bool upper, 
	FormatData fmt
)
{
	char internal[65] = { 0 };
	int len = 0;

	len = SLongToASCII(internal, x, radix, upper);
}

static int WriteULong(
	char *buff, int buffsz,
	int startIndex, unsigned long x,
	int radix, bool upper,
	FormatData fmt
)
{}

/* #if false/true block used for debugging */
#if false
int Vsnprintf(char *buff, int buffsz, const char *fmt, va_list args)
{}

int Vfprintf(FILE *f, const char *fmt, va_list args)
{}

int Vprintf(const char *fmt, va_list args)
{}

int Snprintf(char *buff, int buffsz, const char *fmt, ...)
{}

int Fprintf(FILE *f, const char *fmt, ...)
{}

int Printf(const char *fmt, ...)
{}
#endif
