#pragma once
#include "ofxComponentUI.h"
#include "Global.h"
using namespace ofxComponent;

class TextButton : public Button {
public:
    TextButton(string text = "");
    void onDrawNormal() override;
    void onDrawHovered() override;
    void onDrawPressed() override;
    
    void setText(string txt);
    string getText();
    
    ofColor bgColor, textColor;
    
private:
    void drawSymbol();
    string text;
    ofRectangle bb;
};
