#pragma once
#include "ofxComponentUI.h"
#include "Global.h"
using namespace ofxComponent;

// Up, Down など、Meshを描画するだけのボタンの基底クラス
class SymbolButton : public Button {
public:
    SymbolButton();
    void onDrawNormal() override;
    void onDrawHovered() override;
    void onDrawPressed() override;

    // symbolを書き換えることで、その形のボタンになる
    // symbolは0-1の正規化された次元になっていて、Componentのサイズにフィットするように描画される
    ofMesh symbol;
    
    ofColor color;
    
protected:
    void drawSymbol();
};
