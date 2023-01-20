#pragma once
#include "ofxComponentUI.h"
#include "Counter.h"
#include "MemoButton.h"
using namespace ofxComponent;

class Job : public ofxComponentBase {
public:
    // 無名ジョブ禁止
    Job(string name, int dh = 0, string memo = "");

    void onStart() override;
    void onDraw() override;
    
    string name;
    
    // hoursを10倍した数値
    int deciHours;
    void addCount(int &dh);
    float getHours() {return deciHours * 0.1;} // hoursの値を得る
    int getDeciHours() {return deciHours;}
    void addMemo(string m);
    string getMemo() { return memo; }
    
    // データの内容が変更された通知（サイズ調整、データの保存に使う）
    ofEvent<void> dataChangedEvents;
private:
    shared_ptr<Counter> counter = nullptr;
    
    string memo;
    shared_ptr<MemoButton> memoButton = nullptr;
    const int memoMargin = 2;
    
    void updateHeight();
    
    void showMemoDialog();
};
