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


#define DTED_DSI 80
#define DTED_DATA 3428
#define DTED_DSI_NBLAT (DTED_DSI + 281)
#define DTED_DSI_NBLON (DTED_DSI + 285)
#define DTED_DSI_DATACOV (DTED_DSI + 289)

/*
 * Contains the data of one DTED file.
 */
typedef struct tile {
  int16_t * data;
  int longitudeDimension;
  int latitudeDimension;
} Tile;

#endif

