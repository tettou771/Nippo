#pragma once
#include "ofxComponentUI.h"
#include "Global.h"
using namespace ofxComponent;

// Up, Down 両方の共通部分をまとめたクラス
class SymbolButton : public Button {
public:
    SymbolButton() {;}
    void onDrawNormal() override;
    void onDrawHovered() override;
    void onDrawPressed() override;
protected:
    void drawSymbol();
    ofMesh symbol;
};

// Upボタンの形の定義
class UpButton : public SymbolButton {
public:
    void onStart() override {
        symbol.addVertex(ofVec3f(0, 1));
        symbol.addVertex(ofVec3f(1, 1));
        symbol.addVertex(ofVec3f(0.5, 0));
    }
};

// Downボタンの形の定義
class DownButton : public SymbolButton {
public:
    void onStart() override {
        symbol.addVertex(ofVec3f(0, 0));
        symbol.addVertex(ofVec3f(1, 0));
        symbol.addVertex(ofVec3f(0.5, 1));
    }
};

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
