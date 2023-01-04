#pragma once
#include "ofxComponentUI.h"
#include "Global.h"
#include "Counter.h"
using namespace ofxComponent;


class MemoButton : public Button {
public:
    MemoButton();
    
    void onStart() override;
    void onDrawNormal() override;
    void onDrawHovered() override;
    void onDrawPressed() override;
    
private:
    // ホバー字に表示する文字列
    static string text;
    static ofRectangle textRect;
};
