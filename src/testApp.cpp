#include "testApp.h"

int findNeighbors(int index){
    //////////////////////////////////////////////
    //    i-13[0]      i-12[1]      i-11[2]
    //    i-1[3]        0           i+1[4]
    //    i+11[5]      i+12[6]      i+13[7]
    //////////////////////////////////////////////
    int eNeigh[] = {-13,-12,-11,-1,1,11,12,13};
    if(index % 12 == 0){ // LEFT
        if(index < 12){ // TOP
            int direct[] = {4,6,7};
            int next = ofRandom(3);
            return index + eNeigh[direct[next]];
        } else if(index > 144 - 12){ // BOTTOM
            int direct[] = {1,2,4};
            int next = ofRandom(3);
            return index + eNeigh[direct[next]];
        } else {
            int direct[] = {1,2,4,7,6};
            int next = ofRandom(5);
            return index + eNeigh[direct[next]];
        }
    } else if(index % 12 == 11){ // RIGHT
        if(index < 12){ // TOP
            int direct[] = {3,5,6};
            int next = ofRandom(3);
            return index + eNeigh[direct[next]];
        } else if(index > 144 - 12){ // BOTTOM
            int direct[] = {3,0,1};
            int next = ofRandom(3);
            return index + eNeigh[direct[next]];
        } else {
            int direct[] = {1,0,3,5,6};
            int next = ofRandom(5);
            return index + eNeigh[direct[next]];
        }
    } else if(index < 12){ // TOP
        if(index % 12 == 0){ // LEFT
            int direct[] = {4,6,7};
            int next = ofRandom(3);
            return index + eNeigh[direct[next]];
        } else if(index % 12 == 11){ // RIGHT
            int direct[] = {3,5,6};
            int next = ofRandom(3);
            return index + eNeigh[direct[next]];
        } else {
            int direct[] = {3,5,6,7,4};
            int next = ofRandom(5);
            return index + eNeigh[direct[next]];
        }
    } else if(index > 144 - 12){ // BOTTOM
        if(index % 12 == 0){ // LEFT
            int direct[] = {1,2,4};
            int next = ofRandom(3);
            return index + eNeigh[direct[next]];
        } else if(index % 12 == 11){ //RIGHT
            int direct[] = {3,0,1};
            int next = ofRandom(3);
            return index + eNeigh[direct[next]];
        } else {
            int direct[] = {3,0,1,2,4};
            int next = ofRandom(5);
            return index + eNeigh[direct[next]];
        }
    } else {
        int next = ofRandom(8);
        return index + eNeigh[next];
    }
}


int byteLookupRow[12][3] = {
    {1,     0,      0}, // 0
    {2,     0,      0}, // 1
    {4,     0,      0}, // 2
    {8,     0,      0}, // 3
    {16,    0,      0}, // 4
    {32,    0,      0}, // 5
    {64,    0,      0}, // 6
    {128,   0,      0}, // 7
    {0,     1,      0}, // 8
    {0,     2,      0}, // 9
    {0,     4,      0}, // 10
    {0,     8,      0}, // 11
};
int byteLookupCol[12][3] = {
    {0,     16,     0},     // 0
    {0,     32,     0},     // 1
    {0,     64,     0},     // 2
    {0,     128,    0},     // 3
    {0,     0,      1},     // 4
    {0,     0,      2},     // 5
    {0,     0,      4},     // 6
    {0,     0,      8},     // 7
    {0,     0,      16},    // 8
    {0,     0,      32},    // 9
    {0,     0,      64},    // 10
    {0,     0,      128},   // 11
};



//--------------------------------------------------------------
void testApp::setup(){
//    ofSetVerticalSync(true);
//    ofSetFrameRate(60);
    ofSetCircleResolution(120);
  //  ofSetRectMode(OF_RECTMODE_CENTER);
    
    

    // SETUP SERIAL PORT
    serialA.listDevices();
    
    
	vector <ofSerialDeviceInfo> deviceList = serialA.getDeviceList();
    std::string str2 ("tty.usb");
    
    int a = 0;
    int b = 0;
    for (int i = 0; i < deviceList.size(); i++) {
        std::string str(deviceList[i].getDeviceName());
        unsigned found = str.find(str2);
        if (found != std::string::npos){
            if(a == 0) {
                a = i;
            } else {
                b = i;
            }
        }
    }
    serialA.setup(a, 9600);
    serialB.setup(b, 9600);
    aIsSetup = false;
    bIsSetup = false;
    

    panel.setup("control", ofGetWidth() - 240, 0, 240, 400);
	panel.addPanel("settings", 1, false);
	panel.setWhichPanel("settings");
	panel.addSlider("Build Speed", "VAL_BUILD_SPEED", 1.0, 0.1, 10, false);
    panel.addSlider("Release Speed", "VAL_RELEASE_SPEED", 1.0, 0.1, 10, false);
    panel.addSlider("Min Amplitide", "VAL_MIN_AMP", 2, 25, 600, true);
	panel.addSlider("Max Amplitide", "VAL_MAX_AMP", 120, 50, 600, true);
    panel.addSlider("Change Speed", "VAL_CHANGE_SPEED", 5, 2, 30, false);
//    panel.addToggle("Show Trails", "VAL_TRAILS", false);
//    panel.addToggle("Show Nodes", "VAL_NODES", false);
	panel.loadSettings("settings.xml");
    
    buildSpeed = panel.getValueF("VAL_BUILD_SPEED");
    releaseSpeed = panel.getValueF("VAL_RELEASE_SPEED");
    minAmp = panel.getValueF("VAL_MIN_AMP");
    maxAmp = panel.getValueF("VAL_MAX_AMP");
    changeSpeed = panel.getValueF("VAL_CHANGE_SPEED");
    
    sensitivity = 1;
    

    // COMM VARS
    bFlushA = false;
    bFlushB = false;
    sendByte = false;
    receiveByte = false;
    recieveComplete = true;
    
    
    bytesOut[0] = 0;
    bytesOut[1] = 0;
    bytesOut[2] = 0;
    
    

    
    
    // CEILING VARS
    activeRow = 0;
    activeCol = 0;
    active = ( activeRow * NUM_COLS ) + activeCol;
    for (int y = 0; y < NUM_ROWS; y++) {
        for (int x = 0; x < NUM_COLS; x++) {
            n[y * 12 + x].set(x * 25 + 25, y * 25 + 25, 0);
        }
    }
    
    // FLOOR VARS
    memset(bytesReturned, 0, NUM_SENSORS);
    for (int i = 0; i < NUM_SENSORS; i++) {
        sensorReadings[i] = 0;
        smoothedReadings[i] = 0.0;
    }
    
    // DEBUG UTILS
    fullSequence = false;
    maxSensor = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    panel.update();
    buildSpeed = panel.getValueF("VAL_BUILD_SPEED");
    releaseSpeed = panel.getValueF("VAL_RELEASE_SPEED");
    minAmp = panel.getValueF("VAL_MIN_AMP");
    maxAmp = panel.getValueF("VAL_MAX_AMP");
    changeSpeed = panel.getValueF("VAL_CHANGE_SPEED");

    if(aIsSetup == false) {

        serialA.writeByte('a');
        serialA.writeByte('b');
        serialA.writeByte('c');

        int nRead  = 0;
        unsigned char dataReturned[3];
        memset(dataReturned, 0, 3);
        while( (nRead = serialA.readBytes( dataReturned, 3)) > 0){
        };

        if (dataReturned[0] == 'a' && dataReturned[1] == 'b' && dataReturned[2] == 'c') {
            cout << "Floor SetUp Complete" << endl;
            aIsSetup = true;
            FloorSerial = &serialA;
        }
        if (dataReturned[0] == 'd' && dataReturned[1] == 'e' && dataReturned[2] == 'f') {
            cout << "Ceiling SetUp Complete" << endl;
            aIsSetup = true;
            CloudSerial = &serialA;
        }
        serialA.flush();
    }

    if(bIsSetup == false) {
        serialB.writeByte('a');
        serialB.writeByte('b');
        serialB.writeByte('c');
        
        int nRead  = 0;
        unsigned char dataReturned[3];
		memset(dataReturned, 0, 3);
        while( (nRead = serialB.readBytes( dataReturned, 3)) > 0){
        };

        if (dataReturned[0] == 'a' && dataReturned[1] == 'b' && dataReturned[2] == 'c') {
            cout << "Floor SetUp Complete" << endl;
            bIsSetup = true;
            FloorSerial = &serialB;
        }
        if (dataReturned[0] == 'd' && dataReturned[1] == 'e' && dataReturned[2] == 'f') {
            cout << "Ceiling SetUp Complete" << endl;
            bIsSetup = true;
            CloudSerial = &serialB;
        }
        serialB.flush();
    }

    if(aIsSetup && bIsSetup){
    //    cout << "Serial Ports Setup" << endl;

        activeRow = floor(active / 12);
        activeCol = active - (activeRow * 12);
        
        if(ofGetFrameNum() % changeSpeed == 0 && release){
            int temp = active;
            active = findNeighbors(temp);
            activeRow = floor(active / 12);
            activeCol = active - (activeRow * 12);
            sendByte = true;
        }
        

        // CEILING DATA OUT
        if (sendByte == true && recieveComplete == true) {
            
            for(int i = 0; i < 3; i++){
                bytesOut[i] = byteLookupRow[activeRow][i] + byteLookupCol[activeCol][i];
            }
            
            CloudSerial->writeByte('d');
            CloudSerial->writeByte('e');
            CloudSerial->writeByte('f');
            CloudSerial->writeByte(bytesOut[0]);
            CloudSerial->writeByte(bytesOut[1]);
            CloudSerial->writeByte(bytesOut[2]);
            
       //     CloudSerial->flush();
            
            sendByte = false;
        }// END CEILING DATA OUT


        // GET FLOOR SENSOR DATA
        if (receiveByte == true) {
            recieveComplete = false;
            
            FloorSerial->writeByte('a');
            FloorSerial->writeByte('b');
            FloorSerial->writeByte('c');

            int nRead  = 0;
            memset(bytesReturned, 0, NUM_SENSORS);
            while( (nRead = FloorSerial->readBytes( bytesReturned, NUM_SENSORS)) > 0){
                recieveComplete = false;
            };

            for (int i = 0; i < NUM_SENSORS; i++) {
                sensorReadings[i] = (int)bytesReturned[i];
            }

    //        FloorSerial->flush();
            
            recieveComplete = true;
            receiveByte = false;
        } // END GET FLOOR SENSOR DATA

    /*
        // FLUSH SERIAL CONNECTION - MAYBE GOOD?
        if (bFlush) {
            recieveComplete = false;
            
            serial.writeByte('x');
            serial.writeByte('y');
            serial.writeByte('z');
            
            int nRead  = 0;
            unsigned char dataReturned[2];
            memset(dataReturned, 0, 2);
            while( (nRead = serial.readBytes( dataReturned, 2)) > 0){
                recieveComplete = false;
            };
            if (dataReturned[0] == 'a' && dataReturned[1] == 'b') {
                cout << "flush" << endl;
                serial.flush();
            }
            recieveComplete = true;
            bFlush = false;
        }// END FLUSH SERIAL CONNECTION
    */    

        
        if(building){
            if (power < threshold) {
                power += buildSpeed;
            } else {
                //cout << "full" << endl;
                building = false;
            }
            
        }
        
        if(release){
            if (power > 0.25) {
                power -= releaseSpeed;
            } else {
          
                CloudSerial->writeByte('d');
                CloudSerial->writeByte('e');
                CloudSerial->writeByte('f');
                CloudSerial->writeByte(0);
                CloudSerial->writeByte(0);
                CloudSerial->writeByte(0);
           
          //      CloudSerial->flush();
                
                release = false;
                threshold = ofRandom(minAmp, maxAmp);
                building = true;
            }
        
            
        }
        
        
        
        
        // SMOOTH OUT THE FLOOR VARIABLES
        for (int i = 0; i < NUM_SENSORS; i++) {
            float catchUpSpeed = 0.25;
            float target = sensorReadings[i];
            smoothedReadings[i] = catchUpSpeed * target + (1 - catchUpSpeed) * smoothedReadings[i];
            if(smoothedReadings[i] > maxSensor){
                maxSensor = smoothedReadings[i];
                
                cout << i << " Max " << maxSensor << endl;
            }
            if(smoothedReadings[i] > sensitivity){
                sensitivity = smoothedReadings[i];
            }
        }
        
        if(sensitivity > 1){
            sensitivity *= 0.99;
        } else {
            sensitivity = 1;
        }
        
        
        // CHECK FLOOR DATA FOR ACTIVATION
        for (int i = 0; i < NUM_SENSORS; i++) {
            if (smoothedReadings[i] > sensitivity && release == false) {
                int temp = ofRandom(144);
                active = temp;
                release = true;
            }
        }
        
        
        if(recieveComplete == true) {
            receiveByte = true;
        }
        
        
        // DEBUG - RUN THROUGH THE SEQUENCE IN ORDER
        if (fullSequence && ofGetFrameNum() % 45 == 0){
            if(active < 144) {
                active++;
            } else {
                active = 0;
            }
            sendByte = true;
        }

    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255, 255, 255);

    ofEnableAlphaBlending();
    
    for (int i = 0; i < 144; i++) {
        ofSetColor(0, 0, 0, 60);
        ofRect(n[i].x - 12, n[i].y - 12, 24, 24);
    }
    
    ofDrawBitmapString("Active Node = " + ofToString(active), 50, ofGetHeight() - 25);
    
    for(int i = 0; i < 3; i++){
        ofDrawBitmapString(ofToString(bytesOut[i]), ofGetWidth() / 2 + (i * 50), ofGetHeight() - 25);
    }
    
    
    for (int i = 0; i < NUM_SENSORS; i++) {
        ofDrawBitmapString(ofToString(smoothedReadings[i], 4), ofGetWidth() - 300, ofGetHeight() - ((4 - i)  * 20) - 20);
    }
    
	
    ofPushMatrix();
    ofTranslate(500, 50);
    for (int y = 0; y < NUM_SENSORS / 2; y++) {
        for (int x = 0; x < NUM_SENSORS / 2; x++) {
            ofSetColor(200, 200, 200);
            ofCircle(x * 75, y * 75, 5);
            
            ofSetColor(255, 0, 0, 90);
            ofCircle(x * 75, y * 75, smoothedReadings[y * 2 + x] * 5);
        }
    }
    ofPopMatrix();
    
    
    
    if(release){
        ofSetColor(255, 0, 0, 50);
        ofRect(n[active].x - 12, n[active].y - 12, 24, 24);
        
        ofSetColor(0, 0, 0, 255);
        ofDrawBitmapString(ofToString(activeRow) + "," + ofToString(activeCol), n[active].x, n[active].y);
    }
    
    
    
    ofSetColor(100, 100, 100);
    ofLine(ofGetWidth() - 50, ofGetHeight() - threshold, ofGetWidth(), ofGetHeight() - threshold);
    
    ofSetColor(200, 0, 0);
    ofLine(ofGetWidth() - 50, ofGetHeight() - power, ofGetWidth(), ofGetHeight() - power);
    
    ofSetColor(0, 0, 200);
    ofLine(ofGetWidth() - 100, ofGetHeight() - sensitivity, ofGetWidth(), ofGetHeight() - sensitivity);
    
    ofDrawBitmapString(ofToString(sensitivity), ofGetWidth() - 250, ofGetHeight() - 10);
    
    panel.draw();
    
    ofDisableAlphaBlending();

    
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == ' ') {
        release = false;
 //       fullSequence = !fullSequence;
 //       bFlush = true;
        CloudSerial->writeByte('d');
        CloudSerial->writeByte('e');
        CloudSerial->writeByte('f');
        CloudSerial->writeByte(0);
        CloudSerial->writeByte(0);
        CloudSerial->writeByte(0);
        
        serialA.flush();
        serialB.flush();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    panel.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    panel.mousePressed(x,y,button);
    
    for(int i = 0; i < 144; i++){
        
        if(abs(n[i].x - x) < 12 && abs(n[i].y - y) < 12) {
            active = i;
            release = true;
            //sendByte = true;
        }
    }    
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    panel.mouseReleased();
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    cout << msg.message << endl;
}
void testApp::exit(){
    cout << "exit" << endl;
    CloudSerial->writeByte('d');
    CloudSerial->writeByte('e');
    CloudSerial->writeByte('f');
    CloudSerial->writeByte(0);
    CloudSerial->writeByte(0);
    CloudSerial->writeByte(0);
}