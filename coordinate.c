/******************************************************************************
 * coordinate.c                                          .       .          . *
 * methods to deal with tiles and extract              .   .   /\   .     .   *
 * altitude values                                      .     /  \ .   /\    .*
 *                                                    .    . /    \/\ /  \  . *
 * panoramaMaker                                       .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com       /     /    \    \  *
 ******************************************************************************/


#include "error.h"
#include "typeConst.h"
#include "coordinate.h"
#include <stdlib.h>

/*
 * allocation of memory to store a pointer to a tile in the array
 * space->tile[DIM_DEG*2+1][DIM_DEG*2+1]
 */
void allocSpace(Space * space)
{
  if (!(space->tile = malloc((DIM_DEG*2+1)*sizeof(Tile **))))
  {
    end(E_MALLOC);
  }
  for (int i=0 ; i<DIM_DEG*2+1 ; i++)
  {
    if (!(space->tile[i] = malloc((DIM_DEG*2+1)*sizeof(Tile *))))
    {
      end(E_MALLOC);
    }
    for (int j=0 ; j<DIM_DEG*2+1 ; j++)
    {
      space->tile[i][j] = NULL;
    }
  }
}
