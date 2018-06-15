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

#include <stdint.h>


/*************************
 * Constants and typedef *
 *************************/

/* 
 * DTED file header and data positions.
 */
#define DTED_DSI          80                                                             
#define DTED_DATA         3428                                                          
#define DTED_DSI_NBLAT    (DTED_DSI + 281)                                         
#define DTED_DSI_NBLON    (DTED_DSI + 285)                                         
#define DTED_DSI_DATACOV  (DTED_DSI + 289)  

/*
 * Some constant values.
 */
#define NB_TILES_LON  5                             // Must be odd
#define NB_TILES_LAT  5                             // Must be odd
#define SIZE_SPACE    (NB_TILES_LON * NB_TILES_LAT)
#define DATA_DIR      "data/"

/*
 * Contains the data of one DTED file.
 */
typedef struct tile {
  int16_t * data;
  int longitudeDimension;
  int latitudeDimension;
} Tile;

/*
 * Contains the ensemble of tiles.
 */
typedef struct space {
  Tile* tiles[SIZE_SPACE];
  double originLon;
  double originLat;
} Space;


/*************
 * Functions *
 *************/

void freeTile(Tile*);

Tile * openTile(char*);

Space* initSpace(double, double);

void freeSpace(Space*);

#endif

