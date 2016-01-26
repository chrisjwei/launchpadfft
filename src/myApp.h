#pragma once

#include "ofMain.h"
#include "ofxLaunchpadCustom.h"
#include <cstdlib>

class myApp : public ofBaseApp {
public:
  void setup();
  void update();
  void draw();
  void mousePressed(int x, int y, int button);
  void mouseDragged(int x, int y, int button);
  void dragChange(int x, int y, int button, int reset);

  void setupBoard();
  ofColor getColor(int i);
  void onGridPressed(int row, int col);
  void playWinAnimation();

  ofxLaunchpadCustom launchpad;
  ofxLaunchpadListener listener;
  
  int board[8][8];

  int width, height, minSize, maxSize;
  int win;
};
