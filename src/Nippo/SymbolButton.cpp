#include "SymbolButton.h"

SymbolButton::SymbolButton (){
    color = ofColor(50);
}

void SymbolButton::onDrawNormal() {
    ofSetColor(color);
    drawSymbol();
}

void SymbolButton::onDrawHovered() {
    ofSetColor(color, color.a * 0.5);
    drawSymbol();
}

void SymbolButton::onDrawPressed() {
    ofSetColor(color, color.a * 0.5);
    drawSymbol();
}

void SymbolButton::drawSymbol() {
    ofPushMatrix();
    ofScale(getWidth(), getHeight());
    ofFill();
    symbol.draw();
    ofPopMatrix();
}
