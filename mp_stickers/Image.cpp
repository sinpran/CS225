#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace cs225;

void Image :: lighten(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //lighten an image
      if(pixel.l <= 0.9){
        pixel.l = pixel.l + 0.1;
      }
      else{
        pixel.l = 1.0;
      }
    }
  }
}

void Image :: lighten(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //lighten an image by a certain 'amount'
      pixel.l = pixel.l + amount;
      if(pixel.l >=1){
        pixel.l = 1;
      }
    }
  }
}

void Image :: darken(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //Darken an image
      pixel.l = pixel.l - 0.1;
      if(pixel.l <=0){
        pixel.l = 0;
      }
    }
  }
}

void Image :: darken(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //Darken an image by a certain 'amount'
      pixel.l = pixel.l - amount;
      if(pixel.l <=0){
        pixel.l = 0;
      }
    }
  }
}

void Image :: saturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //Saturate an image
      pixel.s = pixel.s + 0.1;
      if(pixel.s >=1){
        pixel.s = 1;
      }
    }
  }
}

void Image :: saturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //Saturate an image by a certain 'amount'
      pixel.s = pixel.s + amount;
      if(pixel.s >=1){
        pixel.s = 1;
      }
    }
  }
}

void Image :: desaturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //desaturate an image
      pixel.s = pixel.s - 0.1;
      if(pixel.s <=0){
        pixel.s = 0;
      }
    }
  }
}

void Image :: desaturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //Desaturate an image by a certain 'amount'
      pixel.s = pixel.s - amount;
      if(pixel.s <=0){
        pixel.s = 0;
      }
    }
  }
}

void Image :: grayscale(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //Grayscale an image
      pixel.s = 0;
    }
  }
}

void Image :: rotateColor(double degrees){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //Grayscale an image
      pixel.h = pixel.h + degrees;
      if (pixel.h >= 360){
        pixel.h = pixel.h -360;
      }
      else if(pixel.h <= 0){
        pixel.h = 360 - abs(pixel.h);
      }
    }
  }
}

void Image :: illinify(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      //Grayscale an image
      if (315 <= pixel.h || pixel.h <= 135) {
        pixel.h = 11;
      }
      else{
        pixel.h = 216;
      }
    }
  }
}



void Image :: scale(double factor) {
  unsigned originalwidth = this->width();
  unsigned originalheight = this->height();
  unsigned newwidth = this->width() * factor;
  unsigned newheight = this->height() * factor;


  if (factor >= 1){
    this->resize(newwidth, newheight);
    for (unsigned x = newwidth-1; x != (unsigned)-1; x--) {
      for (unsigned y = newheight-1; y != (unsigned) - 1; y--) {
        HSLAPixel &pixel1 = this->getPixel(x, y);
        HSLAPixel &pixel2 = this->getPixel(unsigned((double)x/factor), y/factor);

        pixel1.h = pixel2.h;
        pixel1.s = pixel2.s;
        pixel1.l = pixel2.l;
        pixel1.a = pixel2.a;

      }
    }
  } else{
    for (unsigned x = 0; x < newwidth; x++) {
      for (unsigned y = 0; y < newheight; y++) {
        HSLAPixel &pixel2 = this->getPixel(x, y);
        HSLAPixel &pixel1 = this->getPixel(unsigned((double)x/factor), y/factor);

        pixel2.h = pixel1.h;
        pixel2.s = pixel1.s;
        pixel2.l = pixel1.l;
        pixel2.a = pixel1.a;

      }
    }
    this->resize(newwidth, newheight);
  }
}

void Image::scale(unsigned w, unsigned h){
  double scaleX = (double)w/(double)this->width();
  double scaleY = (double)h/(double)this->height();

  if(scaleY < scaleX){
    scale(scaleY);
  }
  else{
    scale(scaleX);
  }
}
