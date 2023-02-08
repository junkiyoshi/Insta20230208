#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(2);

	this->font.loadFont("fonts/Kazesawa-Extrabold.ttf", 50, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 45 < 5) {

		this->random_seed = ofRandom(1000);
	}

	ofSeedRandom(this->random_seed);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	//string word = "0123456789";
	string word = "LOVE";

	auto number_of_sphere = 150;
	vector<glm::vec2> location_list;
	vector<float> radius_list;

	while (location_list.size() < number_of_sphere) {

		auto location = glm::vec2(ofRandom(-300, 300), ofRandom(-300, 300));
		auto radius = ofRandom(8, 70);
		bool flag = true;
		for (int i = 0; i < location_list.size(); i++) {

			if (glm::distance(location, location_list[i]) < (radius + radius_list[i])) {

				flag = false;
				break;
			}
		}

		if (flag) {

			location_list.push_back(location);
			radius_list.push_back(radius);
		}
	}

	int count = 0;
	while (true) {

		auto all = true;

		for (int i = 0; i < location_list.size(); i++) {

			auto flag = true;
			for (int k = 0; k < location_list.size(); k++) {

				if (i == k) { continue; }

				if (glm::distance(location_list[i], location_list[k]) < (radius_list[i] + radius_list[k])) {

					flag = false;
				}
			}

			if (flag) {

				radius_list[i] += 1;
				all = false;
				break;
			}
		}

		if (all) {

			break;
		}

		count++;
	}

	ofColor color;
	auto param = ofGetFrameNum() % 45 < 5 ? 0.2 : ofGetFrameNum() % 45 < 15 ? ofMap(ofGetFrameNum() % 45, 5, 15, 0.2, 1) : 1;
	for (int i = 0; i < location_list.size(); i++) {

		color.setHsb(ofRandom(255), 255, 255);

		ofPath chara_path = this->font.getCharacterAsPoints(word[ofRandom(word.size())], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		auto angle = ofRandom(-PI * 0.5, PI * 0.5);
		auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 0, 1));

		ofSetColor(color, 128);
		ofFill();
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			outline[outline_index] = outline[outline_index].getResampledByCount(150);
			vector<glm::vec3> vertices = outline[outline_index].getVertices();

			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				glm::vec2 vertex = location_list[i] + glm::vec4(((vertices[vertices_index] - glm::vec2(25, -25)) / 50) * radius_list[i] * 1.5 * param, 0) * rotation;
				ofVertex(vertex);
			}
		}
		ofEndShape(true);

		ofSetColor(color);
		ofNoFill();
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			outline[outline_index] = outline[outline_index].getResampledByCount(150);
			vector<glm::vec3> vertices = outline[outline_index].getVertices();

			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				glm::vec2 vertex = location_list[i] + glm::vec4(((vertices[vertices_index] - glm::vec2(25, -25)) / 50) * radius_list[i] * 1.5 * param, 0) * rotation;
				ofVertex(vertex);
			}
		}
		ofEndShape(true);

		//ofDrawCircle(location_list[i], radius_list[i]);
	}

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}