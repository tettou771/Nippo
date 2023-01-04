#include "TextButton.h"

TextButton::TextButton(string text) {
    setText(text);
}

void TextButton::onDrawNormal() {
    ofSetColor(120);
    drawSymbol();
}

void TextButton::onDrawHovered() {
    ofSetColor(180);
    drawSymbol();
}

void TextButton::onDrawPressed() {
    ofSetColor(180);
    drawSymbol();
}

void TextButton::setText(string txt) {
    text = txt;
    bb = Global::fontMain.getStringBoundingBox(txt, 0, 0);
}

void TextButton::drawSymbol() {
    ofDrawRectangle(0, 0, getWidth(), getHeight());
    
    ofSetColor(255);
    Global::fontMain.drawString(text, (getWidth() - bb.width) / 2 - bb.x, (getHeight() - bb.height) / 2 - bb.y);
}
