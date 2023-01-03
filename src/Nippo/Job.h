#pragma once
#include "ofxComponentUI.h"
#include "Counter.h"
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
    
    static void loadFont();
    
private:
    static ofTrueTypeFont font;
    static bool fontLoaded;
    shared_ptr<Counter> counter;
};
