#include "ofxLaunchpadCustom.h"

ofxLaunchpadCustom::ofxLaunchpadCustom(){
}

void ofxLaunchpadCustom::setup(int port, ofxLaunchpadListener* listener) {
	ofxLaunchpad::setup(port, listener);
	addListener(this);
}