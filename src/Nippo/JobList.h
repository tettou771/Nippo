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
    void hoursChanged();
    void memoChanged();
    void updateJobPositions();
    void load(string dir, int year, int month, int date);
    void save();
    
    ofxCsv data;
    string directory;
    int year, month, date;
    
    // ファイルは年ごとに作られるので、年まであれば十分e
    string toPath(string dir, int year);
    
    vector<shared_ptr<Job> > jobs;
    
private:
    vector<string> weeks;
};
