#pragma once
#include "ofxComponentUI.h"
using namespace ofxComponent;

class UpDownButton : public ofxComponentBase {
public:
    UpDownButton(int *dhPtr, bool isUp);
    void onStart() override;
    void onDraw() override;
    void onMousePressed(ofMouseEventArgs &mouse) override;
private:
    int * deciHoursPtr;
    bool isUp;
};

class Counter : public ofxComponentBase {
public:
    Counter(int *dhPtr);
    
    void onStart() override;
    void onDraw() override;
    void onMousePressed(ofMouseEventArgs &mouse) override;
    void onMouseDragged(ofMouseEventArgs &mouse) override;
    void onMouseReleased(ofMouseEventArgs &mouse) override;

private:
    int * deciHoursPtr;
    bool isDragging = false;
    
    
    
public:
    static ofTrueTypeFont font;
    static bool fontLoaded;
    static void loadFont();
    static const int counterWidth = 60;
    static const int counterHeight = 35;
};
