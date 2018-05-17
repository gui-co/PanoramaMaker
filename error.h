/*****************************************************************************
 * error.h                                              .       .          . *
 * Error functions                                    .   .   /\   .     .   *
 *                                                     .     /  \ .   /\    .*
 *                                                   .    . /    \/\ /  \  . *
 * panoramaMaker                                      .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com      /     /    \    \  *
 *****************************************************************************/


#ifndef ERROR_H
#define ERROR_H

#include <stdarg.h>


void errPrintf(char*, ...);

void warnPrintf(char*, ...);

#endif

