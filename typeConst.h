/*****************************************************************************
 * typesConst.h                                         .       .          . *
 * Definitions of types and constant values           .   .   /\   .     .   *
 *                                                     .     /  \ .   /\    .*
 *                                                   .    . /    \/\ /  \  . *
 * panoramaMaker                                      .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com      /     /    \    \  *
 *****************************************************************************/


#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>


#define DIM_DEG 5


/*
 * Contains the data of one DTED file.
 */
typedef struct tile {
  int16_t * data;
  int longitudeDimension;
  int latitudeDimension;
} Tile;

#endif

