/*****************************************************************************
 * error.c                                              .       .          . *
 * error codes and program exit                       .   .   /\   .     .   *
 *                                                     .     /  \ .   /\    .*
 *                                                   .    . /    \/\ /  \  . *
 * panoramaMaker                                      .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com      /     /    \    \  *
 *****************************************************************************/


#include "error.h"
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


/*
 * Print error message and exit the program. If '>' is the laste character
 * of the format string, errno is read and printed.
 * param fmt: format string.
 */
void errPrintf(char* fmt, ...)
{
	va_list args;

  fprintf(stderr,"[ERROR]: ");
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == '>')
  {
		fprintf(stderr, " %s", strerror(errno));
  }
	fprintf(stderr, "\n");
	exit(2);
}


/*
 * Print warning message and return to program execution. If '>' is the last
 * character, errno is read and printed.
 * param fmt: format string.
 */
void warnPrintf(char* fmt, ...)
{
	va_list args;

	fprintf(stderr, "[WARNING]:  ");
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	
  if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == '>')
  {
		fprintf(stderr, " %s", strerror(errno));
  }
	fprintf(stderr, "\n");
}

