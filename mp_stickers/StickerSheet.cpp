#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

void StickerSheet::copy(const StickerSheet& other){
  stickerMax = other.stickerMax;
  stickerCount = other.stickerCount;
  x = new unsigned[stickerMax];
  y = new unsigned[stickerMax];
  base = new Image(*(other.base));
  Stickers = new Image*[stickerMax];

  unsigned i = 0;
  while(i < stickerCount){
    Stickers[i] = new Image(*other.Stickers[i]);
    x[i] = other.x[i];
    y[i] = other.y[i];
    i++;
  }
}
StickerSheet::StickerSheet(const Image & picture, unsigned max){
  stickerMax = max;
  x = new unsigned[stickerMax];
  y = new unsigned[stickerMax];
  stickerCount = 0;
  base = new Image(picture);
  Stickers = new Image* [stickerMax];
  x[0] =0;
  y[0] = 0;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
  if (this != &other){
    clear();
    copy(other);
  }
  return *this;
}

StickerSheet::StickerSheet(const StickerSheet & other){
  copy(other);
}

void StickerSheet::changeMaxStickers(unsigned max){
  Image** newSticks = new Image*[stickerCount];
  unsigned* newX = new unsigned[stickerCount];
  unsigned* newY = new unsigned[stickerCount];

  for(unsigned i = 0; i < stickerCount; i++){
    newSticks[i] = Stickers[i];
    newX[i] = x[i];
    newY[i] = y[i];
  }
  delete[] x;
  delete[] y;
  delete[] Stickers;
  stickerMax = max;
  Stickers = new Image*[stickerMax];
  x = new unsigned[stickerMax];
  y = new unsigned[stickerMax];

  if(stickerCount <= max){
    for(unsigned i = 0; i < stickerCount; i++){
      Stickers[i] = newSticks[i];
      x[i] = newX[i];
      y[i] = newY[i];
    }
  }
  else{
    for(unsigned i = max; i < stickerCount; i++){
      delete newSticks[i];
      newSticks[i] = nullptr;
    }
    stickerCount = max;
    for(unsigned i = 0; i < stickerCount; i++){
      Stickers[i] = newSticks[i];
      x[i] = newX[i];
      y[i] = newY[i];
    }
  }
  delete[] newSticks;
  delete[] newX;
  delete[] newY;
}

int StickerSheet::addSticker(Image &sticker, unsigned xx, unsigned yy){
  unsigned i =0;
  while (i < stickerMax){
    if (i == stickerCount){
      Stickers[i] = new Image(sticker);
      x[i] = xx;
      y[i] = yy;
      stickerCount++;
      return (int) i;
    }
    i++;
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned xx, unsigned yy){
  if(index >= stickerCount){
    return false;
  }
  else{
    x[index] = xx;
    y[index] = yy;
    return true;
  }
}

void StickerSheet::removeSticker(unsigned index) {
  delete Stickers[index];
  stickerCount--;
  unsigned i = index;
  while (i < stickerMax - 1){
    Stickers[i] = Stickers[i +1];
    x[i] = x[i+1];
    y[i] = y[i +1];
    i++;
  }
  Stickers[stickerMax -1] = nullptr;
  x[stickerMax-1] = 0;
  y[stickerMax-1] = 0;
}

Image* StickerSheet::getSticker(unsigned index){
   if (index < stickerCount){
     return Stickers[index];
   }
   else return NULL;
}

Image StickerSheet::render() const{
  unsigned i = 0;
  Image final(*base);
  while(i < stickerCount){
    unsigned Width = Stickers[i]->width();
    unsigned Height = Stickers[i]->height();
    if(final.width() < Width + x[i]){
      final.resize(Width + x[i], final.height());
    }
    else if(final.height() < Height + y[i]){
      final.resize(final.width(), Height + y[i]);
    }
    for (unsigned x1 = 0; x1 < Width; x1++) {
      for (unsigned y1 = 0; y1 < Height; y1++) {
        HSLAPixel &pixel1 = final.getPixel(x1 + x[i], y1 + y[i]);
        HSLAPixel &pixel2 = Stickers[i]->getPixel(x1, y1);
        if(pixel2.a != 0){
          pixel1.h = pixel2.h;
          pixel1.s = pixel2.s;
          pixel1.l = pixel2.l;
          pixel1.a = pixel2.a;
        }
      }
    }
    i++;
  }
  return final;
}
void StickerSheet::clear(){
  unsigned i =0;
  while(i < stickerCount){
    delete Stickers[i];
    Stickers[i] = nullptr;
    i++;
  }
  delete base;
  delete[] x;
  delete[] y;
  delete[] Stickers;
  x = nullptr;
  y = nullptr;
  Stickers = nullptr;
}

StickerSheet::~StickerSheet(){
  clear();
}
