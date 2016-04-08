#include "ofApp.h"

int posX = 0;
int posY = 0;
string targetX = "0";
string targetY = "0";
string updatedPosStream = "";

void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    font.loadFont("DIN.otf", 9);
    
    
    //------------------------   Serial setup
    bSendSerialMessage = false;
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    int baud = 9600;
    
    serial.setup(0, baud); //open the first device
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
    
}


void ofApp::update(){
    
    if (bSendSerialMessage){
        
        
        targetX = ofToString(posX);
        targetY = ofToString(posY);
        
        //        --------   sample protocol string  ----->  xPos>int;yPos:int</
        
        updatedPosStream = "xPos>" + targetX + ";yPos:" +  targetY + "</" ;
        
        unsigned char* stream = (unsigned char*) updatedPosStream.c_str(); // cast from string to unsigned char* buffer array
        
        serial.writeBytes(&stream[0], updatedPosStream.length());
        
        bSendSerialMessage = false;
    }
}


void ofApp::draw(){
    
    ofSetColor(255);
    
    font.drawString("Serial protcol string: " + updatedPosStream , 10, 50);
}

void ofApp::mouseDragged(int x, int y, int button){
    bSendSerialMessage = true;
    
    posX = mouseX;
    posY = mouseY;
}
