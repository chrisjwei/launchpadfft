#include "myApp.h"

int presses[8][8];
int resizeX = 0;
int resizeY = 0;
int reset = 0;

class MyListener: public ofxLaunchpadListener{
	virtual void automapButtonPressed(int col) {
		switch(col){
			case 0: resizeY = -1; return;
			case 1: resizeY = 1; return;
			case 2: resizeX = -1; return;
			case 3: resizeX = 1; return;
			case 4: reset = 1; return;
			default: return;
		}
	}
	virtual void automapButtonReleased(int col) {
		return;
	}
	virtual void gridButtonPressed(int col, int row) {
		presses[row][col] = 1;
	}
	virtual void gridButtonReleased(int col, int row) {
		return;
	}
	virtual void launchpadEvent(ButtonEvent event) {
		return;
	}
};


void myApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(255);

	ofxLaunchpadListener *listener = new MyListener();
	launchpad.setup(1, listener);
	
	height = 8;
	width = 8;

	fftLive.setMirrorData(false);
  fftLive.setup();

	fftLive.setThreshold(1.0);
  fftLive.setPeakDecay(0.8);
  fftLive.setMaxDecay(0.8);
  fftLive.update();

	setupBoard();
}

void myApp::update(){
	int x, y;

	fftLive.update();

	float * audioData = new float[width];
  fftLive.getFftPeakData(audioData, width);

	for (y = 0; y < height; y++){
		for (x = 0; x < width; x++){
			if (presses[y][x] == 1){
				presses[y][x] = 0;
				onGridPressed(y,x);
			}
		}
	}
	for (x = 0; x < 8; x++){
		float data = audioData[x];
		data = 1-data;
		for (y = 0; y < 8; y++){
			float threshold = 1-((y+1)/(8.0));
			if (data > threshold){
				if (y == 0){
					launchpad.setLedGrid(x, y, ofColor::red);		
				} else if (y < 3){
					launchpad.setLedGrid(x, y, ofColor::yellow);		
				} else {
					launchpad.setLedGrid(x, y, ofColor::green);
				}
				
			} else {
				launchpad.setLedGrid(x, y, ofColor::black);
			}
		}
	}

	delete[] audioData;
}

void myApp::draw(){
	ofSetColor(255);
    
  int w = OFX_FFT_WIDTH;
  int h = OFX_FFT_HEIGHT;
  int x = 20;
  int y = ofGetHeight() - h - 20;
  fftLive.draw(x, y, w, h);
	//ofBackground(0);
	//launchpad.draw(0, 0, ofGetWidth());
}

void myApp::setupBoard(){
	int x, y;
	// reset board
	for (y = 0; y < height; y++){
		for (x = 0; x < width; x++){
			board[y][x] = 0;
			presses[y][x] = 0;
		}
	}
}

ofColor myApp::getColor(int i){
	switch (i){
		case 0: return ofColor::black;
		case -1: return ofColor::red;
		case 1 : return ofColor::yellow;
		default: return ofColor::green;
	}
}

void myApp::onGridPressed(int row, int col){
	
}

void myApp::playWinAnimation(){
}

void myApp::mousePressed(int x, int y, int button) {
}

void myApp::mouseDragged(int x, int y, int button) {
}

void myApp::dragChange(int x, int y, int button, int reset) {
}