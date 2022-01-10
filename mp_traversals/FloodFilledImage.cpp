#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png){
  /** @todo [Part 2] */
  base_ = new PNG(png);
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  path_.push_back(&traversal);
  colors_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  animation.addFrame(*base_);
  for (int i = 0; i < (int)path_.size(); i++)
  {
    ImageTraversal::Iterator begin = path_[i]->begin();
    ImageTraversal::Iterator end = path_[i]->end();
    unsigned count = 0;
    for (ImageTraversal::Iterator it = begin; it != end; ++it)
    {
      if (count == frameInterval)
      {
        animation.addFrame(*base_);
        count = 0;
      }
      count++;
      cs225::HSLAPixel& base = base_->getPixel((*it).x, (*it).y);
      cs225::HSLAPixel newP = colors_[i]->getColor((*it).x, (*it).y);
      base.h = newP.h;
      base.s = newP.s;
      base.l = newP.l;
      base.a = newP.a;
    }
  }
  animation.addFrame(*base_);

  return animation;
}

FloodFilledImage::~FloodFilledImage(){
  delete base_;
}
