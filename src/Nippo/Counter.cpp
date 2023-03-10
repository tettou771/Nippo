#include "Counter.h"

Counter::Counter() {
}

void Counter::onStart() {
    int btnSize = Global::listHeight * 0.6;
    setWidth(Global::listHeight * 1.8 + btnSize * 2);
    setHeight(Global::listHeight);
    auto p = getPos();
    p.x = getParentWidth() - getWidth();
    setPos(p);

    // up down button
    auto down = make_shared<SymbolButton>();
    // ボタンの形の定義
    down->symbol.addVertex(ofVec3f(0, 0));
    down->symbol.addVertex(ofVec3f(1, 0));
    down->symbol.addVertex(ofVec3f(0.5, 1));
    // 左端、高さ中央
    down->setWidth(btnSize);
    down->setHeight(btnSize);
    down->setPos(0, (getHeight() - btnSize)/2);
    ofAddListener(down->clickedEvents, this, &Counter::onDownPressed);
    addChild(down);

    auto up = make_shared<SymbolButton>();
    // ボタンの形の定義
    up->symbol.addVertex(ofVec3f(0, 1));
    up->symbol.addVertex(ofVec3f(1, 1));
    up->symbol.addVertex(ofVec3f(0.5, 0));
    // 右端、高さ中央
    up->setWidth(btnSize);
    up->setHeight(btnSize);
    up->setPos(getWidth() - btnSize, (getHeight() - btnSize)/2);
    ofAddListener(up->clickedEvents, this, &Counter::onUpPressed);
    addChild(up);
}

void Counter::onDraw() {
    //ofDrawRectangle(0, 0, getWidth(), getHeight());
    
    // ホバー中は色を変える
    if (isMouseInside() || isDragging) ofSetColor(120);
    else ofSetColor(50);
    
    // 時間の数値を書く
    string txt = ofToString(float(deciHours) / 10, 1);
    auto rect = Global::fontNumber.getStringBoundingBox(txt, 0, 0);
    Global::fontNumber.drawString(txt, (getWidth() - rect.width) / 2, (getHeight() + rect.height) / 2);
}

void Counter::onMousePressed(ofMouseEventArgs &mouse) {
    isDragging = isMouseInside();
}

void Counter::onMouseDragged(ofMouseEventArgs &mouse) {
    if (!isDragging) return;
    
    // マウスの縦のドラッグ移動量に比例して加減算
    ofVec2f moved = getMousePos() - getPreviousMousePos();
    nudgeHours(-moved.y);
}

void Counter::onMouseReleased(ofMouseEventArgs &mouse) {
    isDragging = false;
}

void Counter::setDeciHours(const int &dh) {
    deciHours = dh;
}

void Counter::nudgeHours(int value) {
    ofNotifyEvent(counterEvent, value);
}

void Counter::onUpPressed() {
    nudgeHours(5); // 0.5 hour
}

void Counter::onDownPressed() {
    nudgeHours(-5); // 0.5 hour
}
