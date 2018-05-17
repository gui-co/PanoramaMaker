/*****************************************************************************
 * tile.c                                               .       .          . *
 * Methodes to deal with DTED files and tiles, the    .   .   /\   .     .   *
 * memory representation of a DTED file                .     /  \ .   /\    .*
 *                                                   .    . /    \/\ /  \  . *
 * panoramaMaker                                      .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com      /     /    \    \  *
 *****************************************************************************/


#include "tile.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <errno.h>


/*
 * Conversion of altitude from DTED file representation to little endian 
 * 2's complement representation.
 * param x: DTED file data.
 * return: Data in little endian and negative in 2's complement.
 */
static int16_t toLittleEndian(int16_t x)
{
  x = (x >> 8) | (x << 8);
  x = x & 0x8000 ? -1 * (x & 0x7FFF) : x;
  return x;
}


/*
 * Free the memory associated to a tile.
 * param tile: Pointer to a tile.
 */
void freeTile(Tile* tile)
{
  free(tile->data);
  free(tile);
}


/* 
 * Open a DTED file, read and store the altitude data.
 * param fileName: Path to a DTED file.
 * return: Pointer to the tile.
 */
Tile* openTile(char* fileName)
{
  FILE* dtedFile;
  long fileSize, expectedSize;
  char headerData[8];
  Tile* tile;
  int nbLon, nbLat, pt;

  // Open file.
  if (!(dtedFile = fopen(fileName, "r")))
  {
    errPrintf("Unable to open %s >", fileName);
  }
    
  fprintf(stdout, "Opening of %s\n", fileName);

  // Get the number of points.
  fseek(dtedFile, 361, SEEK_CUR);
  fread(&headerData, 8, 1, dtedFile);
  nbLat = 1000 * (headerData[0] - 48) + 100 * (headerData[1] - 48) 
          + 10 * (headerData[2] - 48) + (headerData[3] - 48);
  nbLon = 1000 * (headerData[4] - 48) + 100 * (headerData[5] - 48) 
          + 10 * (headerData[6] - 48) + (headerData[7] - 48);
  
  // Check file size.
  fseek(dtedFile, 0, SEEK_END);
  fileSize = ftell(dtedFile);
  fprintf(stdout, "Size: %ld bytes\n", fileSize);
  expectedSize = 3428 + (nbLat * 2 + 12) * nbLon;
  if (fileSize != expectedSize)
  {
    errPrintf("The file has an incorrect size. %ld bytes where expected", 
        expectedSize);
  }

  // Memory allocation.
  if (!(tile = malloc(sizeof(Tile))))
  {
    errPrintf("Unable to allocate memory for the tile >");
  }
  if (!(tile->data = malloc(nbLat * nbLon * sizeof(uint16_t))))
  {
    errPrintf("Unable to allocate memory for the tile data >");
  }

  // Data storage.
  tile->latitudeDimension = nbLat;
  tile->longitudeDimension = nbLon;
  fseek(dtedFile, 3428, SEEK_SET);
  for (int i = 0 ; i < nbLon ; i++)  // Longitude goes W to E.
  {
    fseek(dtedFile, 8, SEEK_CUR);
    for (int j = 0 ; j < nbLat ; j++)  // Lat goes S to N.
    {
      pt = i * nbLon + j;
      fread(&tile->data[pt], 2, 1, dtedFile);
      tile->data[pt] = toLittleEndian(tile->data[pt]);
    }
    fseek(dtedFile, 4, SEEK_CUR);
  }
  
  fclose(dtedFile);
  return tile;
}

