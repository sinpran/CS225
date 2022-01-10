#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel curr = png_.getPixel(x%png_.width(), y % png_.height());
  if(curr.l > .1){
    curr = HSLAPixel(HSLAPixel(200, 1, .5));
  }
  return curr;
}

MyColorPicker::MyColorPicker(string filename){
  png_.readFromFile(filename);
}
