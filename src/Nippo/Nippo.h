#pragma once
#include "ofxComponentUI.h"
#include "Job.h"
#include "JobList.h"
#include "TextButton.h"

using namespace ofxComponent;

class Nippo : public ofxComponentBase {
public:
    Nippo();
    
    // ofxComponentBase
    void onStart() override;
    void onUpdate() override;
    void onDraw() override;
    void onKeyPressed(ofKeyEventArgs &key) override;
    void onMouseReleased(ofMouseEventArgs &mouse) override;

private:
    bool showFolderDialog();
    bool loadSettings();
    bool saveSettings();
    void setDirectory(string path);
    bool loadJob(int year, int month, int date);
    
    // csv file dir
    string directory;
    
    shared_ptr<JobList> jobList;
};
