#include <stdarg.h> /* for va_list */
#include <stdio.h> /* for FILE */

#ifndef PRINTF_H_
#define PRINTF_H_

#define bool unsigned int
#define true 1
#define false 0

int Vsnprintf(char *buff, int buffsz, const char *fmt, va_list args);
int Vfprintf(FILE *f, const char *fmt, va_list args);
int Vprintf(const char *fmt, va_list args);

int Snprintf(char *buff, int buffsz, const char *fmt, ...);
int Fprintf(FILE *f, const char *fmt, ...);
int Printf(const char *fmt, ...);

#endif /* !PRINTF_H_ */
