#include "Job.h"
ofTrueTypeFont Job::font, Job::memoFont;
bool Job::fontLoaded = false;

Job::Job(string name){
    loadFont();
    
    this->name = name;
    deciHours = 0;
    
    setHeight(Counter::counterHeight);
}

void Job::onStart() {
    setWidth(450);
    setHeight(Counter::counterHeight);
    
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

    // memo button (hidden, show on hover)
    memoButton = make_shared<MemoButton>();
    memoButton->setWidth(230);
    memoButton->setHeight(getHeight());
    ofAddListener(memoButton->clickedEvents, this, &Job::showMemoDialog);
    addChild(memoButton);
    
    updateHeight();
}

void Job::onDraw() {
    ofSetColor(50);
    font.drawString(name, 0, (Counter::counterHeight + font.getSize()) / 2);
    
    // メモ
    float margin = 2;
    memoFont.drawString(memo, 0, Counter::counterHeight + memoFont.getSize() + margin);
}

void Job::addCount(int dh) {
    deciHours += dh;
}

void Job::addMemo(string m) {
    if (memo != "") memo += '\n';
    memo += m;
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
    
    // メモ用のフォント 小さくしてロードする
    settings.fontSize = 10;
    memoFont.load(settings);
    
    fontLoaded = true;
}

void Job::updateHeight() {
    if (memo == "") {
        setHeight(Counter::counterHeight);
    }
    else {
        // メモの文字数に合わせて高さを変える
        auto rect = memoFont.getStringBoundingBox(memo, 0, 0);
        setHeight(Counter::counterHeight + 10 + rect.height);
    }
    
    // Jobの位置の再計算リクエスト
    ofNotifyEvent(sizeChangedEvents);
}

void Job::showMemoDialog() {
    auto result = ofSystemTextBoxDialog("メモを入力してください");
    if (result.length() > 1) {
        // メモを追加する
        if (memo != "") memo += '\n';
        memo += result;
        
        updateHeight();
    }
}
