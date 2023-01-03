#include "MemoButton.h"

ofTrueTypeFont MemoButton::font;
bool MemoButton::fontLoaded = false;
string MemoButton::text;
ofRectangle MemoButton::textRect;

MemoButton::MemoButton() {
    loadFont();
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
    font.drawString(text, (getWidth() - textRect.width) / 2, (getHeight() + textRect.height) / 2);
}

void MemoButton::onDrawPressed() {
    onDrawHovered();
}

void MemoButton::loadFont() {
    if (fontLoaded) return;
    // load sans default font
    int fontSize = Counter::counterHeight * 0.6;
    ofTrueTypeFontSettings settings(OF_TTF_SANS, fontSize);
    settings.addRanges(ofAlphabet::Latin);
    font.load(settings);
    
    text = "MEMO";
    textRect = font.getStringBoundingBox(text, 0, 0);
    
    fontLoaded = true;
}
