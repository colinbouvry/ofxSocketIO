#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  isConnected = false;
  //address = "http://127.0.0.1:8888";
  address = "http://127.0.0.1:8001";
  status = "not connected";

  socketIO.setup(address);
  /*
   * You can also pass a query parameter at connection if needed.
   */
  // std::map<std::string,std::string> query;
  // query["token"] = "hello";
  // socketIO.setup(address, query);

  ofAddListener(socketIO.notifyEvent, this, &ofApp::gotEvent);

  ofAddListener(socketIO.connectionEvent, this, &ofApp::onConnection);
}

void ofApp::onConnection () {
  isConnected = true;
  bindEvents();
}

void ofApp::bindEvents () {
  std::string serverEventName = "server-event";
  socketIO.bindEvent(serverEvent, serverEventName);
  ofAddListener(serverEvent, this, &ofApp::onServerEvent);

  std::string pingEventName = "pingy";
  socketIO.bindEvent(pingEvent, pingEventName);
  ofAddListener(pingEvent, this, &ofApp::onPingEvent);

  std::string nspingEventName = "nsping";
  socketIO.bindEvent(nspingEvent, nspingEventName, "nsp");
  ofAddListener(nspingEvent, this, &ofApp::onNSPingEvent);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofDrawBitmapStringHighlight(ofApp::status, 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::gotEvent(string& name) {
  status = name;
}

//--------------------------------------------------------------
void ofApp::onServerEvent (ofxSocketIOData& data) {
  ofLogNotice("ofxSocketIO", data.getStringValue("stringData"));
  ofLogNotice("ofxSocketIO", ofToString(data.getIntValue("intData")));
  ofLogNotice("ofxSocketIO", ofToString(data.getFloatValue("floatData")));
  ofLogNotice("ofxSocketIO", ofToString(data.getBoolValue("boolData")));

  ofxSocketIOData nested = data.getNestedValue("nested");
  ofLogNotice("ofxSocketIO", ofToString(nested.getStringValue("hello")));
}

void ofApp::onPingEvent (ofxSocketIOData& data) {
  ofLogNotice("ofxSocketIO", "pingy");
  std::string pong = "pongy";
  std::string param = "foo";
  socketIO.emit(pong, param);
  /*
   * You can also emit without param
   */
  // socketIO.emit(pong);
}

void ofApp::onNSPingEvent (ofxSocketIOData& data) {
  ofLogNotice("ofxSocketIO", "nsping");
  std::string pong = "nspong";
  std::string param = "foo";
  std::string nsp = "nsp";
  socketIO.emit(pong, param, nsp);
}
