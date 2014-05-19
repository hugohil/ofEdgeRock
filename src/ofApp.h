#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void contactEvent(ofxBox2dContactArgs &e);
		bool contact;
		
		ofxBox2d box2d;
		ofxBox2dCircle ball;
		vector<ofPtr<ofxBox2dRect> > rects;
		float rectRadius;
		float impulse;
};
