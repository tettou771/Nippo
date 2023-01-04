#include "Counter.h"

void SymbolButton::onDrawNormal() {
    ofSetColor(50);
    drawSymbol();
}

void SymbolButton::onDrawHovered() {
    ofSetColor(120);
    drawSymbol();
}

void SymbolButton::onDrawPressed() {
    ofSetColor(120);
    drawSymbol();
}

void SymbolButton::drawSymbol() {
    ofPushMatrix();
    ofScale(getWidth(), getHeight());
    ofFill();
    symbol.draw();
    ofPopMatrix();
}

Counter::Counter(int *dhPtr) {
    deciHoursPtr = dhPtr;
}

void Counter::onStart() {
    int btnSize = Global::listHeight * 0.6;
    setWidth(Global::listHeight * 1.8 + btnSize * 2);
    setHeight(Global::listHeight);
    auto p = getPos();
    p.x = getParentWidth() - getWidth();
    setPos(p);

    // up down button
    auto down = make_shared<DownButton>();
    // 左端、高さ中央
    down->setWidth(btnSize);
    down->setHeight(btnSize);
    down->setPos(0, (getHeight() - btnSize)/2);
    ofAddListener(down->clickedEvents, this, &Counter::onDownPressed);
    addChild(down);

    auto up = make_shared<UpButton>();
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
    string txt = ofToString(float(*deciHoursPtr) / 10, 1);
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

void Counter::nudgeHours(int value) {
    *deciHoursPtr += value;
    
    // 値を制限
    if (*deciHoursPtr < 0) *deciHoursPtr = 0;
    if (*deciHoursPtr > 240) *deciHoursPtr = 240;
}

void Counter::onUpPressed() {
    nudgeHours(5); // 0.5 hour
}

void Counter::onDownPressed() {
    nudgeHours(-5); // 0.5 hour
}
