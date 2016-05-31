#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		int loop(int current, int start, int end);
		void wrapSphere();

		//360 Vision
		GLUquadricObj *quadric;


		unsigned char * pixelout;
		unsigned char * pixelin;
		unsigned char * pixels;

		int width, height;

		int pointer[3];

		ofImage img[2];
		ofImage preview;
		
		double phase;

		int counter = 0;

		int thre; //threshold

		int i, j, u; //itterators

		int red, green, blue;

		int yAxisAdd;

		int inc = 0;


		//GUI
		ofxIntSlider w;
		ofxIntSlider h;
		ofxToggle verticle;
		ofxPanel gui;
};
