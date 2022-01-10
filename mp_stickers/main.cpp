#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png


  Image HappyPikachu;
  HappyPikachu.readFromFile("HappyPikachu.PNG");
  Image Valgrind;
  Valgrind.readFromFile("Valgrind.PNG");
  Image SuprisedPikachu;
  SuprisedPikachu.readFromFile("SuprisedPikachu.PNG");

  StickerSheet image(HappyPikachu, 3);
  image.addSticker(HappyPikachu, 0, 0);
  image.addSticker(Valgrind, 0, 606);
  image.addSticker(SuprisedPikachu, 0, 952);
  Image meme = image.render();

  meme.writeToFile("myImage.png");
  return 0;
}
