#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	//prepare quadric for sphere
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH);


	img[0].loadImage("ocean2.bmp");
	img[1].loadImage("meme.bmp");

	width = img[0].getWidth();
	height = img[0].getHeight();

	pixelout = new unsigned char[width* height * 3];//Assigns length to array
	pixelin = new unsigned char[width* height * 3];


	gui.setup(); // most of the time you don't need a name
	gui.add(w.setup("X", 10, 0, 2000));
	gui.add(h.setup("Y", 10, 0, 2000));
	gui.add(verticle.setup("Y Axis Phase", true));

}
//--------------------------------------------------------------
void ofApp::update(){

	//inc++;

	for (u = 0; u < 1; u++) {

		pixelin = img[u].getPixels();//Gets pixels from video

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {


				thre = 150;

				if (verticle)
					yAxisAdd = loop(j + mouseY * (int)(5 * (u + 1)), 0, height - 1);
				else
					yAxisAdd = j;

				pointer[0] = (j*width + i);
				pointer[u+1] = (yAxisAdd*width + loop(i + inc * (int)(5 * ((u + 1) * (u + 1))), 0, width - 1));

				red = pixelin[pointer[u + 1] * 3 + 0];//red
				green = pixelin[pointer[u + 1] * 3 + 1];//green
				blue = pixelin[pointer[u + 1] * 3 + 2];//blue

				if (u == 0 || green <= blue || green <= red || green < thre) {

					//Draw Pixel

					pixelout[pointer[0] * 3 + 0] = red;
					pixelout[pointer[0] * 3 + 1] = green;
					pixelout[pointer[0] * 3 + 2] = blue;

				}

			}
		}
	}


	preview.setFromPixels(pixelout, width, height, OF_IMAGE_COLOR);//Writes pixels to preview sequence
}

//--------------------------------------------------------------
void ofApp::draw(){
	counter+=40;
	preview.draw(0, 0, width*1.55, height*1.55);

	wrapSphere();

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//---------------=-----------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

int ofApp::loop(int current, int start, int end) {

	if (current > end)
		phase = current - (end * (int)(current / end));
	else if(current < start)
		phase = current + (end * (((int)(current / end)*-1)+1));
	else
		phase = current;

	return phase;
}

//--------------------------------------------------------------
void ofApp::wrapSphere() {

	ofSetColor(255, 255, 255);

	preview.getTextureReference().bind();

	ofPushMatrix();

	
	ofTranslate(ofGetWidth()/2,360, 650);
	ofRotateX(180);

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	ofScale(preview.getWidth(), preview.getHeight());
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST); //enable depth comparisons NEEDED FOR SPHERE DEPTH
	ofDisableArbTex(); //needed for textures to work with gluSphe

	gluSphere(quadric, 200, 100, 100);

	glDisable(GL_DEPTH_TEST);//disable depth comparisons NEEDED FOR FLAT MASK
	ofEnableArbTex(); //needed for textures to work with gluSphe


	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	preview.getTextureReference().unbind();

	ofPopMatrix();
}


