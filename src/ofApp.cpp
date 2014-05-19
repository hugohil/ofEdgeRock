#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableSmoothing();

	box2d.init();
	box2d.enableEvents();
	box2d.registerGrabbing();
	box2d.setGravity(0, 1.3);
	// box2d.createBounds();
	box2d.setFPS(30);

	contact = false;
	ofAddListener(box2d.contactStartEvents, this, &ofApp::contactEvent);

	ball.setPhysics(1, 0.3, 0.8);
	ball.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/3, 40);
	impulse = 0;

	rectRadius = 200;
	ofPtr <ofxBox2dRect> r = ofPtr<ofxBox2dRect>(new ofxBox2dRect);
	r.get()->setPhysics(0.5, 0, 1);
	r.get()->setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()*1.1, rectRadius, rectRadius/20);
	rects.push_back(r);
}

//--------------------------------------------------------------
void ofApp::update(){
	// if(ball.getPosition().y > ofGetHeight()*1.5){
	if(rects.front().get()->getPosition().y - ball.getPosition().y < -(ofGetHeight()/3)){
		cout << "shift" << endl;
		rects.front().get()->setPosition(ofGetWidth()/2, ofGetHeight()*ofRandom(1,2));

		// custom ofxBox2dBaseShape::setPosition() without reseting velocity
		// ball.body->SetTransform(b2Vec2( b2dNum(ofGetWidth()/2), b2dNum(0)), 0);
		ball.setPosition(ofGetWidth()/2, 0);

		// sort(rects.begin(), rects.end(), &ofApp::ySort);
	}

	if(impulse > 0){
		impulse -= 0.05;
	} else if(impulse < 0){
		impulse += 0.05;
	}

	rects.back().get()->setVelocity(0, -1);

	// ball.addForce(impulse, 1);
	box2d.setGravity(impulse, box2d.getGravity().y);

	box2d.update();
}

//--------------------------------------------------------------
void ofApp::contactEvent(ofxBox2dContactArgs &e){
	if(e.a != NULL && e.b != NULL){
		if(e.a->GetType() != b2Shape::e_edge && e.b->GetType() != b2Shape::e_edge){
			contact = true;
		} else {
			contact = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(10,10,30), ofColor(5,5,10), OF_GRADIENT_CIRCULAR);

	ofPushMatrix();
		ofPoint view;
		// regarder tuto unity sur camera super mario
		view.x = ofGetWidth()/2 - ball.getPosition().x;
		view.y = ofGetHeight()/3 - ball.getPosition().y;
		ofTranslate(view);
		
		// ball.setRotation((ball.getVelocity().x*10) * M_PI);
		// ball.setRotation((impulse*10) * M_PI);
		ball.draw();
		
		// ofPushMatrix();
		for (int i = 0; i < rects.size(); ++i){
			rects[i].get()->updateMesh();
			// rects[i].get()->setRotation((impulse*10) * M_PI);
			rects[i].get()->draw();
		}
		// ofPopMatrix();
	ofPopMatrix();

	string info = "ball.y: "+ofToString(ball.getPosition().y)+"\n";
	info += "ball.x: "+ofToString(ball.getPosition().x)+"\n";
	info += "vel: "+ofToString(ball.getVelocity().x)+"\n";
	info += "impulse: "+ofToString(impulse)+"\n";
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == OF_KEY_RIGHT) {
		impulse += 0.1;
	} else if (key == OF_KEY_LEFT){
		impulse -= 0.1;
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
