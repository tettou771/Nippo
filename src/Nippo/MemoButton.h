#pragma once
#include "ofxComponentUI.h"
#include "Counter.h"
using namespace ofxComponent;


class MemoButton : public Button {
public:
    MemoButton();
    
    void onDrawNormal() override;
    void onDrawHovered() override;
    void onDrawPressed() override;
    
private:
    static ofTrueTypeFont font;
    static bool fontLoaded;
    static void loadFont();

    // ホバー字に表示する文字列
    static string text;
    static ofRectangle textRect;
};
