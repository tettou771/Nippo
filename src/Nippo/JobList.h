#pragma once
#include "ofxCsv.h"
#include "ofxComponentUI.h"
#include "Job.h"

using namespace ofxComponent;

class JobList : public ofxComponentBase {
public:
    JobList();
    
    void onStart() override;
    void onDraw() override;
    void onKeyPressed(ofKeyEventArgs &key) override;

    void showNewJobDialog();
    void updateJobPositions();
    void setDirectory(string dir);
    void load(int year, int month, int day);
    void loadToday(); // 最初にこれを呼ばないと、laodPreviousDayなどはうまく機能しない
    void loadPreviousDay();
    void loadNextDay();
    void onDataChanged();
    void save();
    
    ofxCsv data;
    string directory;
    int year, month, day, weekday;
    
    // ファイルは年ごとに作られるので、年まであれば十分
    string toPath(string dir, int year);
    
    vector<shared_ptr<Job> > jobs;
    
    // 日付が変更されたときのイベント
    struct DayChangedEventArgs {
        DayChangedEventArgs(int y, int m, int d) : year(y), month(m), day(d){}
        int year, month, day;
    };
    ofEvent<DayChangedEventArgs> dayChangedEvent;
    
private:
    ofxCsvRow header;
    
    bool isUruuDoshi(int y);
};
