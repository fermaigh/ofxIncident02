#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    
    welcomescreen.loadMovie("movies/welcome.mov");
    welcomescreen.play();
    
    blur.setup(welcomescreen.getWidth(), welcomescreen.getHeight(), 4, .2, 4);
    gameplay.loadMovie("movies/gameplay.mov");
    gameover.loadMovie("movies/gameover.mov");
    
    
    thinkGear.setup();
    ofAddListener(thinkGear.attentionChangeEvent, this, &testApp::attentionListener);  //updates whatever get from the function
    
    
    attention = 0.0;
    
    currBlur = 0.0;
    
    firstPlaySeq = false;
    welcome = true;
    over = false;
    danger = false;
    extreme = false;
    incident = false;
    
    startTime = 0;
    currentTime = 0;
    totalTime = 5;
    flip = true;
    
    counter= 1;
    threshold = 70;
    openThreshold = 63;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    thinkGear.update();
    
    //welcomescreen.update();
    blur.setScale(ofMap(attention, 0.0, 100.0, 4, 1));
    blur.setRotation(ofMap(attention, 0, 100.0, -PI, PI));
    
    if (welcomescreen.getPosition() > 0.9){
        firstPlaySeq = true;
    }
    
    if (firstPlaySeq == false) {
        welcomescreen.update();
        blur.setScale(ofMap(attention, 0.0, 100.0, 4, 1));
        blur.setRotation(ofMap(attention, 0, 100.0, -PI, PI));
    }
    else {
        if (attention < openThreshold){
            welcomescreen.update();
            blur.setScale(ofMap(attention, 0.0, 63.0, 4, 1));
            blur.setRotation(ofMap(attention, 0, 63.0, -PI, PI));
        }
        else {
            welcome = false;
            incident = true;
            welcomescreen.close();
        }
    }
    
    
    if (incident == true){
        gameplay.update();
        
        if (attention < threshold){
            danger = true;
        }
        else {
            danger = false;
            extreme = false;
            flip = true;
        }
        
        if(danger == true && welcome == false){
            
            currentTime = ofGetElapsedTimef();
            
            if (flip == true){
                startTime = ofGetElapsedTimef();
                flip = false;
            }
            
            if (currentTime - startTime < totalTime){
                blur.setScale(ofMap(attention, 0.0, 100.0, 4, 1));
                blur.setRotation(ofMap(attention, 0, 100.0, -PI, PI));
                cout<<"current time:"<<endl;
                cout<<currentTime<<endl;
                cout<<"start time:"<<endl;
                cout<<startTime<<endl;
                extreme = true;
            }
            else {
                gameplay.close();
                gameover.update();
                over = true;
                
            }
        }
        
        if(over==true){
        
        if (gameover.getPosition() > 0.9){
            lastPlaySeq = true;
        }
        
        if (lastPlaySeq == false) {
            gameover.update();
            cout<<"game over"<<endl;
        }
        else {
            welcome = true;
            over = false;
            welcomescreen.update();
            cout<<"game restarted"<<endl;
        }
        }
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    ofSetWindowTitle("Attention = " + ofToString(attention));
    
    
    if (firstPlaySeq == false){
        blur.draw();
        blur.begin();
        welcomescreen.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        welcomescreen.play();
        blur.end();
    } else {
        if (attention < openThreshold) {
            blur.draw();
            blur.begin();
            welcomescreen.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
            welcomescreen.play();
            blur.end();
        }
    }
    
    
    
    if (incident == true && welcome == false && extreme == true){
        blur.draw();
        blur.begin();
        gameplay.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        gameplay.play();
        blur.end();
    }
    else if (incident == true && welcome == false){
        gameplay.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        gameplay.play();
    }
    
    if (over == true) {
        gameover.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        gameover.play();
    }
    
}




void testApp::attentionListener(float &param)
{
    attention = param;
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
