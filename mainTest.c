/*****************************************************************************
 * mainTest.c                                           .       .          . *
 * Main function used to test the different functions .   .   /\   .     .   *
 * during the development of the program               .     /  \ .   /\    .*
 *                                                   .    . /    \/\ /  \  . *
 * panoramaMaker                                      .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com      /     /    \    \  *
 *****************************************************************************/


#include "tile.h"
#include "error.h"
#include "coordinate.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * Print the maximum altitude found in a tile and the corresponding 
 * numbers of seconds in longitude and latitude dimension.
 * param tile: Pointer to the tile.
 */
void printMax(Tile* tile)
{
  int16_t maxAlt;
  int lon;
  int lat;
  int pt;

  maxAlt = 0;
  lon = 0;
  lat = 0;
  
  for (int i = 0 ; i < tile->longitudeDimension ; i++)
  {
    for (int j = 0 ; j < tile->latitudeDimension ; j++)
    {
      pt = i * tile->longitudeDimension + j;
      if (tile->data[pt] > maxAlt)
      {
        maxAlt = tile->data[pt];
        lon = i * (tile->longitudeDimension - 1) / 3600;
        lat = j * (tile->latitudeDimension - 1) / 3600;
      }
    }
  }
  fprintf(stdout,"Altitude max: %dm. Coordinates: %d seconds in longitude "
      "and %d seconds in latitude\n",maxAlt,lon,lat);
}


int main()
{
  /* open and read DTED files */
 
  Tile* t;
  Space* s;
  
  fprintf(stdout, "----------\n");
  fprintf(stdout, "Open a 1 second resolution file and free the memory.\n");
  t = openTile("data/n45_e008_1arc_v3.dt2");
  freeTile(t);
  fprintf(stdout, "----------\n\n");

  fprintf(stdout, "----------\n");
  fprintf(stdout, "Open a file with different resolutions in the two "
      "dimensions.\n");
  t = openTile("data/n59_e009_1arc_v3.dt2");
  freeTile(t);
  fprintf(stdout, "----------\n\n");

  fprintf(stdout, "----------\n");
  fprintf(stdout, "Read the data of a tile in the north hemisphere, east of "
      "Prime Meridian (Mont blanc).\n");
  t = openTile("data/n45_e006_1arc_v3.dt2");
  printMax(t);
  freeTile(t);
  fprintf(stdout, "----------\n\n");

  fprintf(stdout, "----------\n");
  fprintf(stdout,"Read data of a tile in south hemisphere, west of Prime "
      "Meridian (Aconcagua).\n");
  t = openTile("data/s33_w071_1arc_v3.dt2");
  printMax(t);
  freeTile(t);
  fprintf(stdout, "----------\n\n");

  fprintf(stdout, "----------\n");
  fprintf(stdout,"Init space around Mt Blanc (6.86 east ; 45.83 north).\n");
  s = initSpace(6.86, 45.83);
  printMax(s->tiles[SIZE_SPACE / 2]);
  freeSpace(s);
  fprintf(stdout, "----------\n\n");

  fprintf(stdout, "----------\n");
  fprintf(stdout,"Init space around Aconcagua (70.01 west ; 32.65 south).\n");
  s = initSpace(-70.01, -32.65);
  printMax(s->tiles[SIZE_SPACE / 2]);
  freeSpace(s);
  fprintf(stdout, "----------\n\n");

  fprintf(stdout, "----------\n");
  fprintf(stdout,"Target a point with distance and bearing.\n");
  double targetLon;
  double targetLat;
  fprintf(stdout, "Distance: 100 km, bearing: 60 degres, from 6.86 east - "
      "45.83 north.\n");
  target(6.86, 45.83, 100000, 60, &targetLon, &targetLat);
  fprintf(stdout, "Waited latitude: 46.27 ; obtained: %lf\n", targetLat);
  fprintf(stdout, "Waited longitude: 7.99 ; obtained: %lf\n", targetLon);
  fprintf(stdout, "\n");
  fprintf(stdout, "Distance: 100 km, bearing: 0 degres, from 6.86 east - "
      "45.83 north.\n");
  target(6.86, 45.83, 100000, 0, &targetLon, &targetLat);
  fprintf(stdout, "Waited latitude: 46.73 ; obtained: %lf\n", targetLat);
  fprintf(stdout, "Waited longitude: 6.86 ; obtained: %lf\n", targetLon);
  fprintf(stdout, "\n");
  fprintf(stdout, "Distance: 100 km, bearing: 60 degres, from 6.86 west - "
      "45.83 north.\n");
  target(-6.86, 45.83, 100000, 60, &targetLon, &targetLat);
  fprintf(stdout, "Waited latitude: 46.27 ; obtained: %lf\n", targetLat);
  fprintf(stdout, "Waited longitude: -5.73 ; obtained: %lf\n", targetLon);
  fprintf(stdout, "\n");
  fprintf(stdout, "Distance: 100 km, bearing: 60 degres, from 6.86 east - "
      "45.83 south.\n");
  target(6.86, -45.83, 100000, 60, &targetLon, &targetLat);
  fprintf(stdout, "Waited latitude: -45.37 ; obtained: %lf\n", targetLat);
  fprintf(stdout, "Waited longitude: 7.97 ; obtained: %lf\n", targetLon);
  fprintf(stdout, "----------\n\n");

  return 0;
}

