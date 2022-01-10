#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
* Calculates a metric for the difference between two pixels, used to
* calculate if a pixel is within a tolerance.
*
* @param p1 First pixel
* @param p2 Second pixel
* @return the difference between two HSLAPixels
*/
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
double h = fabs(p1.h - p2.h);
double s = p1.s - p2.s;
double l = p1.l - p2.l;

// Handle the case where we found the bigger angle between two hues:
if (h > 180) { h = 360 - h; }
h /= 360;

return sqrt( (h*h) + (s*s) + (l*l) );
}
/**
* Default iterator constructor.
*/
ImageTraversal::Iterator::Iterator(){
 traversal = NULL;
 unsigned int width = 0;
 unsigned int height = 0;
 unsigned int W = base_.width();
 unsigned int H = base_.height();

 v.resize(W, std::vector<bool>(H));
 while(width < W){
   while(height < H){
     v[width][height] = false;
     height++;
   }
   width++;
 }
}

bool ImageTraversal::Iterator::isAllowed(Point point){
 Point temp = point;
 if(temp.y >= base_.height() || temp.x >= base_.width())
    return false;
 if (temp.y < base_.height() && temp.x < base_.width()){
   HSLAPixel & start = base_.getPixel(start_.x, start_.y);
   HSLAPixel & pos = base_.getPixel(temp.x, temp.y);
   if(calculateDelta(start, pos) < tolerance_){
     if(v[temp.x][temp.y] == false){
       return true;
     }
   }
 }
 return false;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* imaget,PNG png, Point point, double d){
traversal = imaget;
base_ = png;
start_ = point;
pos_ = point;
tolerance_ = d;

unsigned int width = 0;
unsigned int height = 0;
unsigned int W = base_.width();
unsigned int H = base_.height();

v.resize(W, std::vector<bool>(H));
while(width < W){
  while(height < H){
    v[width][height] = false;
    height++;
  }
  width++;
}

if (!isAllowed(pos_) == false)
  v[pos_.x][pos_.y] = true;
}

/**
* Iterator increment opreator.
*
* Advances the traversal of the image.
*/
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
 v[pos_.x][pos_.y]=true;
 Point right, left, above, below;

 right = Point(pos_.x+1,pos_.y);
 left = Point(pos_.x-1,pos_.y);
 above = Point(pos_.x,pos_.y-1);
 below = Point(pos_.x,pos_.y+1);

 if(isAllowed(right)){ traversal->add(right);}
 if(isAllowed(below)){ traversal->add(below);}
 if(isAllowed(left)) {traversal->add(left);}
 if(isAllowed(above)) {traversal->add(above);}

 while(traversal->empty()!=true && isAllowed(traversal->peek())!=true)
 {
   traversal->pop();
   if(traversal->empty())
   {
     return *this;
   }
 }
 if(traversal->empty()==false)
 {
   pos_ = traversal->peek();
   return *this;
 }
 else
 {
   traversal = NULL;
   return *this;
 }
 return *this;
}

/**
* Iterator accessor opreator.
*
* Accesses the pos_ Point in the ImageTraversal.
*/
Point ImageTraversal::Iterator::operator*() {
 	return pos_;
}

/**
* Iterator inequality operator.
*
* Determines if two iterators are not equal.
*/
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
 	bool thisEmpty = false;
  bool otherEmpty = false;

  if(traversal == NULL)
    thisEmpty = true;
  if (other.traversal == NULL)
    otherEmpty = true;

  if(!thisEmpty)
    thisEmpty = traversal->empty();
  if (!otherEmpty)
    otherEmpty = other.traversal->empty();

  if(thisEmpty && otherEmpty)
    return false;
  else if(!thisEmpty && !otherEmpty)
    return traversal != other.traversal;
  else
    return true;
}
