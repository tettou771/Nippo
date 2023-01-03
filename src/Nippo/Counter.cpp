#include "Counter.h"

ofTrueTypeFont Counter::font;
bool Counter::fontLoaded = false;

UpDownButton::UpDownButton(int *dhPtr, bool isUp) : deciHoursPtr(dhPtr), isUp(isUp) {
    int size = 20;
    setWidth(size);
    setHeight(size);
}

void UpDownButton::onStart() {
}

void UpDownButton::onDraw() {
    ofPushMatrix();
    ofScale(getWidth(), getHeight());
    
    if (isMouseInside()) ofSetColor(120);
    else ofSetColor(50);

    ofFill();
    
    // up
    if (isUp) {
        ofDrawTriangle(0, 1, 1,1,0.5,0);
    }
    // down
    else {
        ofDrawTriangle(0, 0, 1,0,0.5,1);

    }
    
    ofPopMatrix();
}

void UpDownButton::onMousePressed(ofMouseEventArgs &mouse) {
    if (!isMouseInside()) return;
    
    int nudge = 10; // 1hour
    if (isUp) *deciHoursPtr += nudge;
    else *deciHoursPtr -= nudge;
    
    // 値を制限
    if (*deciHoursPtr < 0) *deciHoursPtr = 0;
    if (*deciHoursPtr > 240) *deciHoursPtr = 240;
}

Counter::Counter(int *dhPtr) {
    loadFont();
    deciHoursPtr = dhPtr;
    
    setWidth(counterWidth);
    setHeight(counterHeight);
}

void Counter::onStart() {
    
}

void Counter::onDraw() {
    ofNoFill();
    ofDrawRectangle(0, 0, getWidth(), getHeight());
    
    if (isMouseInside() || isDragging) ofSetColor(120);
    else ofSetColor(50);
    string txt = ofToString(float(*deciHoursPtr) / 10, 1);
    font.drawString(txt, 0, (getHeight() + font.getSize()) / 2);
}

void Counter::onMousePressed(ofMouseEventArgs &mouse) {
    isDragging = isMouseInside();
}

void Counter::onMouseDragged(ofMouseEventArgs &mouse) {
    if (!isDragging) return;
    
    ofVec2f moved = getMousePos() - getPreviousMousePos();
    *deciHoursPtr -= moved.y;
    
    // 値を制限
    if (*deciHoursPtr < 0) *deciHoursPtr = 0;
    if (*deciHoursPtr > 240) *deciHoursPtr = 240;
}

void Counter::onMouseReleased(ofMouseEventArgs &mouse) {
    isDragging = false;
}

void Counter::loadFont() {
    if (fontLoaded) return;
    // load sans default font
    int fontSize = counterHeight * 0.6;
    font.load(OF_TTF_SANS, fontSize);
    fontLoaded = true;
}
