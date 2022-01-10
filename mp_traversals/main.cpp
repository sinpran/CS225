
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG vegito2;    vegito2.readFromFile("vegito2.png");

    FloodFilledImage image(vegito2);

    DFS dfs1(vegito2, Point(0, 0), 0.1);
    DFS dfs2(vegito2, Point(859, 0), 0.1);
    DFS dfs3(vegito2, Point(0, 1280), 0.1);
    DFS dfs4(vegito2, Point(600, 550), 0.1);
    DFS dfs5(vegito2, Point(800, 800), 0.1);
    DFS dfs6(vegito2, Point(200, 900), 0.1);
    DFS dfs7(vegito2, Point(835, 737), 0.1);

    BFS bfs1(vegito2, Point(0, 0), 0.1);
    BFS bfs2(vegito2, Point(859, 0), 0.1);
    BFS bfs3(vegito2, Point(0, 1280), 0.1);
    BFS bfs4(vegito2, Point(600, 550), 0.1);
    BFS bfs5(vegito2, Point(800, 800), 0.1);
    BFS bfs6(vegito2, Point(200, 900), 0.1);
    BFS bfs7(vegito2, Point(835, 737), 0.1);

    MyColorPicker fourstar("fourstar.png");
    SolidColorPicker red(HSLAPixel(0, 1, .5));

    image.addFloodFill(dfs1, red);
    image.addFloodFill(dfs2, red);
    image.addFloodFill(dfs3, red);
    image.addFloodFill(dfs4, red);
    image.addFloodFill(dfs5, red);
    image.addFloodFill(dfs6, red);
    image.addFloodFill(dfs7, red);

    image.addFloodFill(bfs1, fourstar);
    image.addFloodFill(bfs2, fourstar);
    image.addFloodFill(bfs3, fourstar);
    image.addFloodFill(bfs4, fourstar);
    image.addFloodFill(bfs5, fourstar);
    image.addFloodFill(bfs6, fourstar);
    image.addFloodFill(bfs7, fourstar);

    Animation animation = image.animate(80000);

    PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
    lastFrame.writeToFile("myFloodFill.png");
    animation.write("myFloodFill.gif");

  return 0;
}
