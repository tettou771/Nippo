#include "SymbolButton.h"

SymbolButton::SymbolButton (){
    normalColor = ofColor(50);
    hoveredColor = pressedColor = ofColor(150);
}

void SymbolButton::onDrawNormal() {
    ofSetColor(normalColor);
    drawSymbol();
}

void SymbolButton::onDrawHovered() {
    ofSetColor(hoveredColor);
    drawSymbol();
}

void SymbolButton::onDrawPressed() {
    ofSetColor(pressedColor);
    drawSymbol();
}

void SymbolButton::drawSymbol() {
    ofPushMatrix();
    ofScale(getWidth(), getHeight());
    ofFill();
    symbol.draw();
    ofPopMatrix();
}
