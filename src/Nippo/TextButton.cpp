#include "TextButton.h"

TextButton::TextButton(string text) {
    setText(text);
    bgColor = ofColor(50);
    textColor = ofColor(255);
}

void TextButton::onDrawNormal() {
    ofSetColor(bgColor);
    drawSymbol();
}

void TextButton::onDrawHovered() {
    ofSetColor(bgColor, bgColor.a * 0.5);
    drawSymbol();
}

void TextButton::onDrawPressed() {
    ofSetColor(bgColor, bgColor.a * 0.5);
    drawSymbol();
}

void TextButton::setText(string txt) {
    text = txt;
    bb = Global::fontMain.getStringBoundingBox(txt, 0, 0);
}

void TextButton::drawSymbol() {
    ofDrawRectangle(0, 0, getWidth(), getHeight());
    
    ofSetColor(textColor);
    Global::fontMain.drawString(text, (getWidth() - bb.width) / 2 - bb.x, (getHeight() - bb.height) / 2 - bb.y);
}
