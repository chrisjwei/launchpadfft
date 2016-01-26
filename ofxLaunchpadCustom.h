#pragma once

#include "ofxLaunchpad.h"

class ofxLaunchpadCustom : public ofxLaunchpad, public ofxLaunchpadListener {
public:
	ofxLaunchpadCustom();
	void setup(int port, ofxLaunchpadListener* listener);
};