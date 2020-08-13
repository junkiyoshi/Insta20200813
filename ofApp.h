#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {}
	void keyReleased(int key) {}
	void mouseMoved(int x, int y) {}
	void mouseDragged(int x, int y, int button) {}
	void mousePressed(int x, int y, int button) {}
	void mouseReleased(int x, int y, int button) {}
	void mouseEntered(int x, int y) {}
	void mouseExited(int x, int y) {}
	void windowResized(int w, int h) {}
	void dragEvent(ofDragInfo dragInfo) {}
	void gotMessage(ofMessage msg) {}

	void sort(vector<glm::vec2>& vertices);

	ofxBox2d box2d;
	
	vector<ofColor> color_list;

	vector<glm::vec2> walker_list;
	vector<glm::vec2> walker_noise_seed_list;

	vector<shared_ptr<ofxBox2dPolygon>> polygon_list;
	vector<float> polygon_lile_list;
	vector<ofColor> polygon_color_list;
};