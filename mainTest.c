/******************************************************************************
 * mainTest.c                                            .       .          . *
 * Main function used to test the different functions  .   .   /\   .     .   *
 * during the development of the program                .     /  \ .   /\    .*
 *                                                    .    . /    \/\ /  \  . *
 * panoramaMaker                                       .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com       /     /    \    \  *
 ******************************************************************************/


#include "typeConst.h"
#include "tile.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * print the maximum altitude found in a tile (Tile type) and the corresponding
 * indices in the tile->data array
 * param tile: tile where the data will be read
 */
void printMax(Tile tile)
{
  int16_t maxA = 0;
  int maxI = 0;
  int maxJ = 0;
  
  for (int i=0;i<tile.longitudeDimension;i++)
  {
    for (int j=0;j<tile.latitudeDimension;j++)
    {
      if (tile.data[i][j] > maxA)
      {
        maxA = tile.data[i][j];
        maxI = i;
        maxJ = j;
      }
    }
  }
  fprintf(stdout,"Altitude: %dm. Coordinates: i=%d (longitude) and j=%d (latitude)\n",maxA,maxI,maxJ);
}


int main()
{
  Tile tile={NULL,0,0};

  /* open and read DTED files */
  
  fprintf(stdout,"Test 1: open and read a 1 second resolution file\n");
  openTile("data/n45_e008_1arc_v3.dt2",&tile);
  freeTile(&tile);
  
  fprintf(stdout,"Test 2: free the occupied space and open a tile with different resolutions in the two dimensions\n");
  freeTile(&tile);
  openTile("data/n59_e009_1arc_v3.dt2",&tile);

  fprintf(stdout,"Test 4: read the data of a tile with E longitudes and N latitude (Mt blanc)\n");
  freeTile(&tile);
  openTile("data/n45_e006_1arc_v3.dt2",&tile);
  printMax(tile);

  fprintf(stdout,"Test 4: read the data of a tile with W longitudes and S latitude (Aconcagua)\n");
  freeTile(&tile);
  openTile("data/s33_w071_1arc_v3.dt2",&tile);
  printMax(tile);

  return 0;
}
