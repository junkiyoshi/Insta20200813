#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);

	this->box2d.init();
	this->box2d.setGravity(0, 50);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();

	ofColor color;
	vector<int> hex_list = { 0xef476f, 0xffd166, 0x06d6a0, 0x118ab2, 0x073b4c };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->color_list.push_back(color);
	}

	for (int i = 0; i < 15; i++) {

		this->walker_list.push_back(glm::vec2());
		this->walker_noise_seed_list.push_back(glm::vec2(ofRandom(1000), ofRandom(1000)));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < this->walker_list.size(); i++) {

		this->walker_list[i] = glm::vec2(
			ofMap(ofNoise(this->walker_noise_seed_list[i].x, ofGetFrameNum() * 0.005), 0, 1, 0, ofGetWidth()),
			ofMap(ofNoise(this->walker_noise_seed_list[i].y, ofGetFrameNum() * 0.005), 0, 1, 0, ofGetHeight() * 0.25)
		);
	}

	if (ofGetFrameNum() % 3 == 0) {

		for (int i = 0; i < this->walker_list.size(); i++) {

			vector<glm::vec2> vertices;
			for (int k = i + 1; k < this->walker_list.size(); k++) {

				if (glm::distance(this->walker_list[i], this->walker_list[k]) < 50) {

					vertices.push_back(this->walker_list[k] - this->walker_list[i]);
				}
			}

			if (vertices.size() >= 2) {

				this->sort(vertices);
				for (int m = 0; m < vertices.size() - 1; m++) {

					auto polygon = make_shared<ofxBox2dPolygon>();

					polygon->addVertex(this->walker_list[i].x, this->walker_list[i].y);
					polygon->addVertex(this->walker_list[i].x + vertices[m].x, this->walker_list[i].y + vertices[m].y);
					polygon->addVertex(this->walker_list[i].x + vertices[m + 1].x, this->walker_list[i].y + vertices[m + 1].y);

					polygon->setPhysics(1.0, 0.7, 0.3);
					polygon->create(box2d.getWorld());

					this->polygon_list.push_back(polygon);
					this->polygon_lile_list.push_back(255);
					this->polygon_color_list.push_back(this->color_list[(int)ofRandom(this->color_list.size())]);
				}
			}
		}
	}

	for (int i = this->polygon_list.size() - 1; i > -1; i--) {

		this->polygon_lile_list[i] -= 1;

		if (this->polygon_lile_list[i] < 0) {

			this->polygon_list.erase(this->polygon_list.begin() + i);
			this->polygon_lile_list.erase(this->polygon_lile_list.begin() + i);
			this->polygon_color_list.erase(this->polygon_color_list.begin() + i);
		}
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofSetColor(39);
	for (int i = 0; i < this->walker_list.size(); i++) {

		ofDrawCircle(this->walker_list[i], 4);

		for (int k = i + 1; k < this->walker_list.size(); k++) {

			if (glm::distance(this->walker_list[i], this->walker_list[k]) < 50) {

				ofDrawLine(this->walker_list[i], this->walker_list[k]);
			}
		}
	}

	for (int i = 0; i < this->polygon_list.size(); i++) {

		if (this->polygon_lile_list[i] > 128) {

			ofSetColor(this->polygon_color_list[i]);
		}
		else {

			ofSetColor(this->polygon_color_list[i], ofMap(this->polygon_lile_list[i], 128, 0, 255, 0));
		}
		this->polygon_list[i]->draw();
	}
}

//--------------------------------------------------------------
void ofApp::sort(vector<glm::vec2>& vertices) {

	glm::vec2 tmp;
	for (int i = 0; i < vertices.size(); i++) {

		for (int k = i + 1; k < vertices.size(); k++) {

			if (vertices[i].x < vertices[k].x) {

				tmp = vertices[i];
				vertices[i] = vertices[k];
				vertices[k] = tmp;
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}