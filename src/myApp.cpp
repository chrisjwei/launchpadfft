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
		cout << "Automap " << col << " released" << endl;
	}
	virtual void gridButtonPressed(int col, int row) {
		presses[row][col] = 1;
	}
	virtual void gridButtonReleased(int col, int row) {
		cout << "Grid " << row << ","  << col << " released" << endl;
	}
	virtual void launchpadEvent(ButtonEvent event) {
		cout << "button event" << endl;
	}
};


void myApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(255);

	ofxLaunchpadListener *listener = new MyListener();
	launchpad.setup(1, listener);
	width = 5;
	height = 5;
	minSize = 3;
	maxSize = 8;
	win = 0;
	setupBoard();
}

void myApp::update(){
	int x, y;
	for (y = 0; y < height; y++){
		for (x = 0; x < width; x++){
			if (presses[y][x] == 1){
				presses[y][x] = 0;
				onGridPressed(y,x);
			}
		}
	}
	if (win){
		win = 0;
		playWinAnimation();
		setupBoard();
		return;
	}
	for (y = 0; y < 8; y++){
		for (x = 0; x < 8; x++){
			launchpad.setLedGrid(x, y, getColor(board[y][x]));
		}
	}
	if (reset == 1){
		reset = 0;
		setupBoard();
	}
	if (resizeX != 0){
		width += resizeX;
		if (width < minSize){
			width = minSize;
		}
		if (width > maxSize){
			width = maxSize;
		}
		resizeX = 0;
		setupBoard();
	}
	if (resizeY != 0){
		height += resizeY;
		if (height < minSize){
			height = minSize;
		}
		if (height > maxSize){
			height = maxSize;
		}
		resizeY = 0;
		setupBoard();
	}
}

void myApp::draw(){
	ofBackground(0);
	launchpad.draw(0, 0, ofGetWidth());
}

void myApp::setupBoard(){
	int x, y;
	// reset board
	for (y = 0; y < 8; y++){
		for (x = 0; x < 8; x++){
			board[y][x] = -1;
			presses[y][x] = 0;
		}
	}
	for (y = 0; y < height; y++){
		for (x = 0; x < width; x++){
			board[y][x] = 0;
		}
	}
	x = rand() % width;
	y = rand() % height;
	board[y][x] = 1;
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
	board[row][col] = !board[row][col];
	if (row + 1 < height){
		board[row+1][col] = !board[row+1][col];
	}
	if (row - 1 >= 0){
		board[row-1][col] = !board[row-1][col];
	}
	if (col + 1 < width){
		board[row][col+1] = !board[row][col+1];
	}
	if (col - 1 >= 0){
		board[row][col-1] = !board[row][col-1];
	}
	win = 1;
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			if (board[y][x]){
				win = 0;
			}
		}
	}
}

void myApp::playWinAnimation(){
	int x, y;
	for (y = 0; y < 8; y++){
		for (x = 0; x < 8; x++){
			launchpad.setLedGrid(x, y, ofColor::green);
		}
	}
	ofSleepMillis(3000);
}

void myApp::mousePressed(int x, int y, int button) {
}

void myApp::mouseDragged(int x, int y, int button) {
}

void myApp::dragChange(int x, int y, int button, int reset) {
}