#include "MemoButton.h"

string MemoButton::text = "MEMO";
ofRectangle MemoButton::textRect;

MemoButton::MemoButton() {
}

void MemoButton::onStart() {
    textRect = Global::fontMain.getStringBoundingBox(text, 0, 0);
}

void MemoButton::onDrawNormal() {
    // hidden
}

void MemoButton::onDrawHovered() {
    ofSetColor(0, 100);
    ofFill();
    ofDrawRectangle(0, 0, getWidth(), getHeight());

    // 中央寄せで文字を書く
    ofSetColor(255);
    Global::fontMain.drawString(text, (getWidth() - textRect.width) / 2, (getHeight() + textRect.height) / 2);
}

void MemoButton::onDrawPressed() {
    onDrawHovered();
}
