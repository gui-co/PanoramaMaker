/******************************************************************************
 * typesConst.h                                          .       .          . *
 * definitions of types and constant values            .   .   /\   .     .   *
 *                                                      .     /  \ .   /\    .*
 *                                                    .    . /    \/\ /  \  . *
 * panoramaMaker                                       .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com       /     /    \    \  *
 ******************************************************************************/


#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>


/*
 * a tile contains the data of one altitude file (DTED file) in a 
 * two dimensions array of longitudeDimension and latitudeDimension
 * lengths
 */
typedef struct tile {
  int16_t ** data;
  int longitudeDimension;
  int latitudeDimension;
} Tile;

#endif
