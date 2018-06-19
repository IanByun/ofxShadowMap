#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	model.loadModel("amua.obj");
	model.setRotation(0,180,0,0,1);
	model.setScaleNormalization(false);
	shadowMap.setup(1024*16);

	light.enable();
	camera.setDistance(200);
	ground.setOrientation(ofQuaternion(-90.f, ofVec3f(1.f, 0.f, 0.f)));
	ground.enableColors();
	for (int i = 0; i < ground.getMesh().getVertices().size(); i++)
		ground.getMesh().getColors().push_back(ofFloatColor::gray);

	enableShadows.addListener(this, &ofApp::listenerFunction);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();

//	light.setPosition(-200,200,200);
//	light.lookAt({0,0,0});
	float longitude = ofMap(ofGetMouseX(), 0, ofGetWidth(), -90, 90);
	float latitude = ofMap(ofGetMouseY(), 0, ofGetHeight(), -60, -10);
	float radius = 200;
	ofVec3f centerPoint(0, 20 , 0);
	ofQuaternion q = ofQuaternion(longitude, ofVec3f(0, 1, 0)) * ofQuaternion(latitude, ofVec3f(1, 0, 0));

	ofVec4f p (0.f, 0.f, 1.f, 0.f); // p is a direction, not a position, so .w == 0

	p = p * ofMatrix4x4(q); // rotate p on unit sphere based on quaternion
	p = p * radius; // scale p by radius from its position on unit sphere
	light.setGlobalPosition(centerPoint + p);
	light.setOrientation(q);

	if(enableShadows){
		shadowMap.updateShadow(light, frustumSize, 1, farClip);
		model.drawFaces();
		shadowMap.endUpdate();
	}

	camera.begin();
	shadowMap.castShadow();
	ground.draw();
	shadowMap.endCast();
	model.drawFaces();
	light.draw();
	camera.end();

	ofDisableDepthTest();
	shadowMap.getDepthTexture().draw(ofGetWidth()-256, 0, 256, 256);
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	constexpr auto amount = 1;
	ofPoint positon = model.getPosition();
	switch (key = tolower((char)key))
	{
	case 'w': 
		positon += ofVec3f(0, 0, -amount);
		break;
	case 's':
		positon += ofVec3f(0, 0, +amount);
		break;
	case 'a':
		positon += ofVec3f(-amount, 0, 0);
		break;
	case 'd':
		positon += ofVec3f(+amount, 0, 0);
		break;
	}
	model.setPosition(positon.x, positon.y, positon.z);
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
