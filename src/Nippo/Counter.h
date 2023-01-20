#pragma once
#include "ofxComponentUI.h"
#include "Global.h"
#include "SymbolButton.h"
using namespace ofxComponent;

// 数値とUp,Downボタンが一緒になったクラス
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
    
    void nudgeHours(int value);
    void onUpPressed();
    void onDownPressed();
};
