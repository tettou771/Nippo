#include "Job.h"

Job::Job(string name, int dh, string memo){
    this->name = name;
    this->deciHours = dh;
    this->memo = memo;
    updateHeight();
}

void Job::onStart() {
    setWidth(450);
    setHeight(Global::listHeight);
    int w = getParentWidth();
    setWidth(w);
    
    counter = make_shared<Counter>();
    counter->setPos(w - 60, 0);
    counter->setDeciHours(deciHours);
    ofAddListener(counter->counterEvent, this, &Job::addCount);
    addChild(counter);
    
    // memo button (hidden, show on hover)
    memoButton = make_shared<MemoButton>();
    memoButton->setWidth(getWidth() - Global::listHeight * 4);
    memoButton->setHeight(getHeight());
    ofAddListener(memoButton->clickedEvents, this, &Job::showMemoDialog);
    addChild(memoButton);
    
    updateHeight();
}

void Job::onDraw() {
    ofDrawRectangle(0, 0, getWidth(), getHeight());

    ofSetColor(50);
    Global::fontMain.drawString(name, 0, (Global::listHeight + Global::fontMain.getSize()) / 2);
    
    // メモ
    if (memo != "") {
        Global::fontSmall.drawString(memo, 0, Global::listHeight + Global::fontSmall.getSize() + memoMargin);
    }
}

void Job::addCount(int &dh) {
    deciHours += dh;
    if (deciHours < 0) deciHours = 0;
    if (deciHours > 240) deciHours = 240;
    
    if (counter) counter->setDeciHours(deciHours);
    
    ofNotifyEvent(dataChangedEvents);
}

void Job::addMemo(string m) {
    if (memo != "") memo += '\n';
    memo += m;
    updateHeight();
    ofNotifyEvent(dataChangedEvents);
}

void Job::updateHeight() {
    if (memo == "") {
        setHeight(Global::listHeight);
    }
    else {
        // メモの文字数に合わせて高さを変える
        auto rect = Global::fontSmall.getStringBoundingBox(memo, 0, 0);
        setHeight(Global::listHeight + memoMargin + rect.height);
    }
}

void Job::showMemoDialog() {
    auto result = ofSystemTextBoxDialog("メモを入力してください");
    if (result.length() > 1) {
        // メモを追加する
        addMemo(result);
    }
}
