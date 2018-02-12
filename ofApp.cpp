#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true); // sync with vertical refresh rate
	ofxGuiSetFont(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);

	graph.setup(100, 100, 800, 400);
	graph.setName("spring-mass-damper system wave");     // it automatically loads setting file, (sample.xml)
	graph.setDx(2.0); // which means delta of time
	graph.setColor(ofColor::white);  // ofColor(255,255,255)
	graph.setBufSize(1000);  
	graph.setLabel({ "y0","u" });

	frame = 0;

	gui.setup("parametor");
	gui.add(kk.setup("K", 1.0, 0.0, 5.0));
	gui.add(mm.setup("M", 0.1, 0.0, 1.0));
	gui.add(cc.setup("C", 0.1, 0.0, 1.0));

	//double  k = 1.0;
	//double  m = 0.1;
	//double  c = 0.1;

	MatrixXd A(2, 2);
	A<< 0,1,-kk / mm,-cc / mm;
	MatrixXd B(2, 1);
	B << 1, 1 / mm;
	MatrixXd C(1, 2);
	C << 0, 1;
	MatrixXd D(1, 1);
	D << 1;

	MatrixXd X(2, 1);
	X(0, 0) = 1;
	X(1, 0) = 0;
	MatrixXd dX(2, 1);
	dX(0, 0) = 0;
	dX(1, 0) = 0;


	MatrixXd u(1, 1);
	u << 0;
	MatrixXd Y(1, 1);
	Y(0, 0) = 0;

	 AA = A;
	 BB = B;
	 CC = C;
	 DD = D;
	 XX = X;
	 dXX = dX;

	 uu=u;
	 YY=Y;

	  dt = 0.01;
	  tt = 0.0;
}

//--------------------------------------------------------------
void ofApp::update() {
	frame++;

	AA << 0, 1, -kk / mm, -cc / mm;
	BB << 1, 1 / mm;

	double TT = 100.0;
	uu(0, 0) = sin(2.0*M_PI/ TT*frame);

	RungeKutta(dXX, XX, uu, tt, dt, AA, BB, CC, DD);
	
	YY = CC*XX;
	tt += dt;

	vector<float>value;
	value.push_back(YY(0, 0));
	//value.push_back(XX(0, 0));
	//value.push_back(XX(1, 0));
	value.push_back(uu(0,0));

	graph.add(value);
	//graph2.add(-test);

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(50, 50, 50);
	gui.draw();

	graph.draw();
	//graph2.draw();

	string info = "";
	info += "A mat = \n";
	info += serialize(AA);
	info += "B mat = \n";
	info += serialize(BB);
	info += "C mat = \n";
	info += serialize(CC);
	info += "D mat = \n";
	info += serialize(DD);

	string info2 = "";
	info2 += "X mat = \n";
	info2 += serialize(XX);
	info2 += "dX mat = \n";
	info2 += serialize(dXX);
	info2 += "u mat = \n";
	info2 += serialize(uu);
	info2 += "Y mat = \n";
	info2 += serialize(YY);

	ofSetColor(240, 240, 240);
	ofFill();
	ofRect(20, ofGetHeight() * 2 /3, ofGetWidth()/2.0, ofGetHeight() / 3 -20);
	
	ofSetColor(240, 240, 0);
	if(uu(0, 0)==1)	ofSetColor(240, 0, 0);
	ofRect(ofGetWidth() / 2.0 + 60, ofGetHeight() * 2 / 3, ofGetWidth() / 3.0, ofGetHeight() / 3 - 20);

	ofSetColor(0);
	ofDrawBitmapString(info, 50, ofGetHeight() * 2 / 3 +40);
	ofDrawBitmapString(info2, ofGetWidth()/4.0, ofGetHeight() * 2 / 3 + 40);

	string info3="Control input";
	ofDrawBitmapString(info3, ofGetWidth() / 2.0 + 60, ofGetHeight() * 2 / 3 + 40);


	ofSetColor(255);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		graph.saveSettings(); // save setting graph size and position
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
	//uu(0, 0) = 1;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	//uu(0, 0) = 0;

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
