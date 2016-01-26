#include "ofMain.h"
#include "myApp.h"

int main() {
	ofSetupOpenGL(480, 480, OF_WINDOW);
	ofRunApp(new myApp());
}
