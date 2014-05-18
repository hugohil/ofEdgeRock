#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableSmoothing();

	box2d.init();
	box2d.setGravity(0, 1.3);
	// box2d.createBounds();
	box2d.setFPS(30);

	ofPtr <ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
	edge.get()->addVertex((ofGetWidth()/2) - (edgeRadius/2), ofGetHeight()/1.1);
	edge.get()->addVertex((ofGetWidth()/2) + (edgeRadius/2), ofGetHeight()/1.1);
	edge.get()->create(box2d.getWorld());
	edges.push_back(edge);

	ball.setPhysics(1, 0.1, 0.1);
	ball.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/3, 40);
	pBall_y = ball.getPosition().y;
}

//--------------------------------------------------------------
void ofApp::update(){
	box2d.update();
	if(theta <= 0){
		theta += 0.1;
	} else if (theta >= 0){
		theta -= 0.1;
	}
	ofPtr <ofxBox2dEdge> e = edges.back();
	e.get()->setRotation(theta);
	// e.get()->body->SetTransform(e.get()->body->GetLocaldCenter(), DEG_TO_RAD * theta);
	e.get()->updateShape();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(10,10,30), ofColor(5,5,10), OF_GRADIENT_CIRCULAR);

	// ofPushMatrix();
		ofPoint view;
		// regarder tuto unity sur camera super mario
		view.x = 0;
		view.y = ofGetHeight()/3 - ball.getPosition().y;
		// view.y = pBall_y - ball.getPosition().y;
		// ofTranslate(view);
		// box2d.getWorld()->ShiftOrigin(view);

		ball.draw();
		
		// ofPushMatrix();
			edges.back().get()->draw();
		// ofPopMatrix();
	// ofPopMatrix();

	string info = ofToString(ball.getPosition().y)+"\n";
	info += ofToString(theta);
	ofDrawBitmapString(info, 30, 30);
	pBall_y = ball.getPosition().y;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == OF_KEY_RIGHT) {
		theta += 0.2;
	} else if (key == OF_KEY_LEFT){
		theta -= 0.2;
	}
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
