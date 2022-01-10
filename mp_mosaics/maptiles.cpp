/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<3>> points;
     map<Point<3>, TileImage*> map;
     for (auto iter = theTiles.begin(); iter != theTiles.end(); iter++) {
     	LUVAPixel pixel_ = iter->getAverageColor();
     	Point<3> point_ = convertToXYZ(pixel_);
     	points.push_back(point_);
     	map[point_] = &*iter;
     }
     KDTree<3> kdt_avgcolor(points);
     MosaicCanvas * base = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
     for (int i = 0; i < base->getRows(); i++) {
     	for (int j = 0; j < base->getColumns(); j++) {
     		Point<3> goal_ = convertToXYZ(theSource.getRegionColor(i, j));  
     		Point<3> best_ = kdt_avgcolor.findNearestNeighbor(goal_);
     		TileImage* correct_tile = map[best_];
     		base->setTile(i, j, correct_tile);
     	}
     }
     return base;
}
