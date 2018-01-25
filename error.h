/******************************************************************************
 * error.h                                               .       .          . *
 * error codes and program exit                        .   .   /\   .     .   *
 *                                                      .     /  \ .   /\    .*
 *                                                    .    . /    \/\ /  \  . *
 * panoramaMaker                                       .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com       /     /    \    \  *
 ******************************************************************************/


#ifndef ERROR_H
#define ERROR_H

#define E_FILE_NOT_FOUND 1
#define E_FILE_NOT_CORRECT 2
#define E_MALLOC 3
#define E_FREAD 4


/*
 * array to store usefull data for error explanation
 */
char errorData[200];

void end(int);

#endif
