#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto R = 300.f;
	auto r = 100.f;
	auto u = 0.f;
	auto u_step = 10.f;
	auto v_step = 5.f;
	
	ofColor color;
	int threshold = (ofGetFrameNum() * 2) % 360;
	auto threshold_len = 60;
	auto threshold_min = threshold - threshold_len < 0 ? 360 + threshold - threshold_len : threshold - threshold_len;
	auto threshold_max = threshold + threshold_len >= 360 ? (360 - threshold - threshold_len) * -1 : threshold + threshold_len;

	for (int i = 0; i < 9; i++) {

		color.setHsb(ofMap(i, 0, 9, 0, 255), 200, 255);

		ofRotate(20);
		vector<glm::vec3> vertices;
		for (auto v = 0; v < 360; v += v_step) {

			if (((threshold_min < threshold_max) && (threshold_min < v && v < threshold_max)) ||
				((threshold_min > threshold_max) && (threshold_min < v || v < threshold_max))) {

				vertices.clear();
				vertices.push_back(this->make_point(R, r, u, v));
				vertices.push_back(this->make_point(R, r, u + u_step, v + v_step));
				vertices.push_back(this->make_point(R, r, u, v + v_step));
				vertices.push_back(this->make_point(R, r, u - u_step, v));

				ofSetColor(color);
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);
			}

			ofSetColor(189);
			ofDrawLine(this->make_point(R, r, u + 0.5, v), this->make_point(R, r, u + u_step + 0.5, v + v_step));
			ofDrawLine(this->make_point(R, r, u - 0.5, v + v_step), this->make_point(R, r, u - u_step - 0.5, v));

			u += u_step;
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}