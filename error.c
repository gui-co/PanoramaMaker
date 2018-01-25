/******************************************************************************
 * error.c                                               .       .          . *
 * error codes and program exit                        .   .   /\   .     .   *
 *                                                      .     /  \ .   /\    .*
 *                                                    .    . /    \/\ /  \  . *
 * panoramaMaker                                       .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com       /     /    \    \  *
 ******************************************************************************/


#include "error.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * exit the program when receiving different error codes
 * param eCode: the code of the error
 */
void end(int err)
{
  if (err == E_FILE_NOT_FOUND)
  {
    fprintf(stderr,"Unable to open %s. File not found!\n",errorData);
    exit(1);
  }

  if (err == E_FILE_NOT_CORRECT)
  {
    fprintf(stderr,"File %s not correct!\n",errorData);
    exit(1);
  }

  if (err == E_MALLOC)
  {
    fprintf(stderr,"Memory allocation error!\n");
    exit(1);
  }

  if (err == E_FREAD)
  {
    fprintf(stderr,"Error while reading %s file!\n",errorData);
    exit(1);
  }

  else
  {
    exit(1);
  }
}
