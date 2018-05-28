/*****************************************************************************
 * tile.h                                               .       .          . *
 * Methodes to deal with HGT files and tiles, the     .   .   /\   .     .   *
 * memory representation of a HGT file                 .     /  \ .   /\    .*
 *                                                   .    . /    \/\ /  \  . *
 * panoramaMaker                                      .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com      /     /    \    \  *
 *****************************************************************************/


#ifndef TILE_H
#define TILE_H

#include "typeConst.h"


void freeTile(Tile*);

Tile * openTile(char*);

#endif

