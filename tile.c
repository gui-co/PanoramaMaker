/******************************************************************************
 * tile.c                                                .       .          . *
 * methodes to deal with DTED files and tiles, the     .   .   /\   .     .   *
 * memory representation of a DTED file                 .     /  \ .   /\    .*
 *                                                    .    . /    \/\ /  \  . *
 * panoramaMaker                                       .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com       /     /    \    \  *
 ******************************************************************************/


#include "tile.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


/*
 * conversion of altitude from DTED file representation to little endian 
 * 2's complement representation
 * param x: 16bits integer from DTED file
 * returns: 16bits integer in little endian and negative in 2's complement
 */
static int16_t dtedToLittleEndian(int16_t x)
{
  /* big to little endian */
  x = (x>>8)|(x<<8);

  /* for negative number: from magnitude to 2's complement */
  if (x&0x8000)
  {
    x=-1*(x&0x7FFF);
  }

  return x;
}


/*
 * memory allocation to save the HGT file content
 * param tile: adress of a tile (Tile type)
 */
void allocTile(Tile * tile)
{
  if (!(tile->data = malloc(tile->longitudeDimension*sizeof(int16_t*))))
  {
    end(E_MALLOC);
  }
  for (int i=0 ; i<tile->longitudeDimension ; i++)
  {
    if (!(tile->data[i] = malloc(tile->latitudeDimension*sizeof(int16_t))))
    {
      end(E_MALLOC);
    }
  }
}


/*
 * free the memory associated to a tile
 * param tile: address of a tile (Tile type)
 */
void freeTile(Tile * tile)
{
  for (int i=0 ; i<tile->longitudeDimension ; i++)
  {
    free(tile->data[i]);
  }
  free(tile->data);
  tile->data = NULL;
  tile->longitudeDimension = 0;
  tile->latitudeDimension = 0;
}


/* 
 * open a DTED file and read the data to put them in memory
 * param fileName: path to a DTED file
 * param tile: address of a tile (Tile type) where the data will be saved
 */
void openTile(char* fileName, Tile * tile)
{
  FILE* dtedFile;
  long size;
  char data[8];

  /* file opening */
  if (!(dtedFile = fopen(fileName,"r")))
  {
    sprintf(errorData,"%s",fileName);
    end(E_FILE_NOT_FOUND);
  }
    
  fprintf(stdout,"Opening of %s\n",fileName);

  /* the number of points in the two dimensions is obtained from the header */
  fseek(dtedFile,361,SEEK_CUR);
  fread(&data,8,1,dtedFile);
  tile->latitudeDimension = 1000*(data[0]-48)+100*(data[1]-48)+10*(data[2]-48)+(data[3]-48);
  tile->longitudeDimension = 1000*(data[4]-48)+100*(data[5]-48)+10*(data[6]-48)+(data[7]-48);

  /* the size is checked according to the numbers of points */
  fseek(dtedFile,0,SEEK_END);
  size = ftell(dtedFile);
  fprintf(stdout,"Size: %ld bytes\n",size);

  if (size != 3428+(tile->latitudeDimension*2+12)*(tile->longitudeDimension))
  {
    sprintf(errorData,"%s",fileName);
    end(E_FILE_NOT_CORRECT);
  }

  /* memory allocation */
  allocTile(tile);

  /* data are read and saved according to the resolutions */
  /* i (j) increases when longitude (latitude) goes W (S) to E (N) */
  fseek(dtedFile,3428,SEEK_SET);
  for (int i=0 ; i<tile->longitudeDimension ; i++)
  {
    fseek(dtedFile,8,SEEK_CUR);
    for (int j=0 ; j<tile->latitudeDimension ; j++)
    {
      if (!fread(&tile->data[i][j],2,1,dtedFile))
      {
        sprintf(errorData,"%s",fileName);
        end(E_FILE_NOT_CORRECT);
      }
      tile->data[i][j] = dtedToLittleEndian(tile->data[i][j]);
    }
    fseek(dtedFile,4,SEEK_CUR);
  }
  
  fclose(dtedFile);
}
