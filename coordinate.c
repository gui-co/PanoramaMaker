/*****************************************************************************
 * coordinate.c                                         .       .          . *
 *                                                    .   .   /\   .     .   *
 *                                                     .     /  \ .   /\    .*
 *                                                   .    . /    \/\ /  \  . *
 * panoramaMaker                                      .    /     /  \    \   *
 * Guillaume Communie - guillaume.communie@gmail.com      /     /    \    \  *
 *****************************************************************************/


#include "coordinate.h"
#include <math.h>


/*
 * Get the longitude / latitude af a destination point given distance and 
 * bearing from origin point.
 * param originLon: Longitude of the origin point.
 * param originLat: Latitude of the origin point.
 * param distance: distance to destination point.
 * param bearing: bearing to the destination point.
 * param targetLon: To store the destination point longitude.
 * param targetLat: To store the destination point latitude.
 */
void target(double originLon, double originLat, double distance, 
    double bearing, double* targetLon, double* targetLat)
{
  double angDist;

  angDist = distance / EARTH_RADIUS;

  // Angles in radians.
  originLon = originLon * M_PI / 180;
  originLat = originLat * M_PI / 180;
  bearing = bearing * M_PI / 180;

  *targetLat = asin(sin(originLat) * cos(angDist) 
             + cos(originLat) * sin(angDist) * cos(bearing));
  *targetLon = originLon + atan2(sin(bearing) * sin(angDist) * cos(originLat), 
               cos(angDist) - sin(originLat) * sin(*targetLat));

  // Back to degrees.
  *targetLat = *targetLat * 180 / M_PI;
  *targetLon = *targetLon * 180 / M_PI;
}

