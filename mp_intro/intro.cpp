#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <complex>
#include <cmath>
using namespace cs225;
using namespace std;

void rotate(string inputFile, string outputFile) {
  // TODO: Part 2

  PNG originalpic, newpic;

  originalpic.readFromFile(inputFile);
  newpic.readFromFile(outputFile);
  unsigned w = originalpic.width();
  unsigned h = originalpic.height();
  newpic.resize(w, h);

  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      HSLAPixel & pixel1 = originalpic.getPixel(x, y);
      HSLAPixel & pixel2 = newpic.getPixel(w-1-x, h-1-y);

      pixel2.h = pixel1.h;
      pixel2.s = pixel1.s;
      pixel2.l = pixel1.l;
      pixel2.a = pixel1.a;
    }
  }
  newpic.writeToFile(outputFile);
}



PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);

  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {

      HSLAPixel & pixel = png.getPixel(x, y);
      complex <double> coord((double) x/height, (double) y/width);
      complex <double> position(0, 0);
      int iterations = 0;
      for (;abs(position) < 2 && iterations <= 20; iterations++) {
        position = pow(position,2) + coord;
      }
      if (iterations <30){
        pixel.h = 315*iterations;
        pixel.s = 1;
        pixel.l = 0.7;
        pixel.a = 1;
      }
      else{
        pixel.h = 0;
        pixel.s = 0;
        pixel.l = 0;
        pixel.a = 0;
      }
    }
  }
  return png;
}
