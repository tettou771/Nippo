#include "Job.h"
ofTrueTypeFont Job::font;
bool Job::fontLoaded = false;

Job::Job(string name){
    loadFont();
    
    this->name = name;
    deciHours = 0;
    
    setHeight(Counter::counterHeight);
}

void Job::onStart() {
    counter = make_shared<Counter>(&deciHours);
    counter->setPos(300, 0);
    addChild(counter);
    
    // up down button
    auto down = make_shared<UpDownButton>(&deciHours, false);
    down->setPos(250, (getHeight() - down->getHeight())/2);
    addChild(down);
    auto up = make_shared<UpDownButton>(&deciHours, true);
    up->setPos(360, (getHeight() - down->getHeight())/2);
    addChild(up);

}

void Job::onDraw() {
    ofSetColor(50);
    font.drawString(name, 0, (getHeight() + font.getSize()) / 2);
}

void Job::addCount(int dh) {
    deciHours += dh;
}

void Job::loadFont() {
    if (fontLoaded) return;
    // load sans default font
    int fontSize = Counter::counterHeight * 0.6;
#ifdef TARGET_OS_MAC
    ofTrueTypeFontSettings settings("ヒラギノ角ゴシック", fontSize);
#else
    ofTrueTypeFontSettings settings(OF_TTF_SANS, fontSize);
#endif
    settings.addRanges(ofAlphabet::Latin);
    settings.addRanges(ofAlphabet::Japanese);
    font.load(settings);
    fontLoaded = true;
}
