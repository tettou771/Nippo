#pragma once
#include "ofxComponentUI.h"
#include "Counter.h"
#include "MemoButton.h"
using namespace ofxComponent;

class Job : public ofxComponentBase {
public:
    // 無名ジョブ禁止
    Job(string name);

    void onStart() override;
    void onDraw() override;
    
    string name;
    
    // hoursを10倍した数値
    int deciHours;
    void addCount(int dh);
    float getHours() {return deciHours * 0.1;} // hoursの値を得る
    void addMemo(string m);
    string getMemo() { return memo; }
    
    // サイズ変更の通知をするためのイベント
    ofEvent<void> memoChangedEvents;
private:
    shared_ptr<Counter> counter;
    
    string memo;
    shared_ptr<MemoButton> memoButton;
    const int memoMargin = 2;
    
    void updateHeight();
    
    void showMemoDialog();
};
