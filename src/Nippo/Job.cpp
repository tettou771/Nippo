#include "Job.h"

Job::Job(string name){
    this->name = name;
    deciHours = 0;
}

void Job::onStart() {
    setWidth(450);
    setHeight(Global::listHeight);
    int w = getParentWidth();
    setWidth(w);
    
    counter = make_shared<Counter>(&deciHours);
    counter->setPos(w - 60, 0);
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
    Global::fontSmall.drawString(memo, 0, Global::listHeight + Global::fontSmall.getSize() + memoMargin);
}

void Job::addCount(int dh) {
    deciHours += dh;
}

void Job::addMemo(string m) {
    if (memo != "") memo += '\n';
    memo += m;
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
    
    // Jobの位置の再計算リクエスト
    ofNotifyEvent(memoChangedEvents);
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
