/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet{
  public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned xx, unsigned yy);
    bool translate(unsigned index, unsigned xx, unsigned yy);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    Image render() const;

  private:
    unsigned stickerMax;
    Image* base;
    Image** Stickers;
    unsigned* x;
    unsigned* y;
    unsigned stickerCount;
    void clear();
    void copy(const StickerSheet& other);

};
