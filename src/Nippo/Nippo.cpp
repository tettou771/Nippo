#include "Nippo.h"

Nippo::Nippo() {
    
}

void Nippo::onStart() {
    Global::prepare();
    
    setWidth(ofGetWidth());
    setHeight(ofGetHeight());
    
    // リストのオブジェクト
    jobList = make_shared<JobList>();
    int margin = 6;
    jobList->setWidth(getWidth() - margin * 2);
    jobList->setHeight(getHeight());
    jobList->setPos(margin, 50);
    addChild(jobList);
    
    // ジョブ追加のボタン
    auto addJobButton = make_shared<TextButton>("Add");
    addJobButton->setWidth(Global::listHeight * 2);
    addJobButton->setHeight(Global::listHeight);
    addJobButton->setPos(margin, margin);
    ofAddListener(addJobButton->clickedEvents, &(*jobList), &JobList::showNewJobDialog);
    addChild(addJobButton);
    
    // 設定ファイルが正常に読まれたとき
    if (loadSettings()) {
    }
    // ファイルがないとき、ダイアログでフォルダ指定してもらう
    else{
        bool canceled = showFolderDialog();
        if (!canceled) {
            // キャンセルならアプリを終了する
            OF_EXIT_APP(1);
        }
        // フォルダ指定されたら、そのディレクトリで実行
    }
    
    jobList->load(directory, ofGetYear(), ofGetMonth(), ofGetDay());
}

void Nippo::onUpdate() {
    
}

void Nippo::onDraw() {
    // 今日の日付
    stringstream daystr;
    string week = "";
    switch (ofGetWeekday()) {
        case 0: week = "日"; break;
        case 1: week = "月"; break;
        case 2: week = "火"; break;
        case 3: week = "水"; break;
        case 4: week = "木"; break;
        case 5: week = "金"; break;
        case 6: week = "土"; break;
        default: break;
    }
    daystr << ofGetYear() << "年 " << ofGetMonth() << "月 " << ofGetDay() << "日 (" << week << ")";
    auto daystrrect = Global::fontMain.getStringBoundingBox(daystr.str(), 0, 0);
    ofSetColor(100);
    Global::fontMain.drawString(daystr.str(), (getWidth() - daystrrect.width) / 2, 4 + daystrrect.height);
}

void Nippo::onKeyPressed(ofKeyEventArgs &key) {
    if (key.key == ' ') {
        bool b = showFolderDialog();
        if (b) {
            jobList->load(directory, ofGetYear(), ofGetMonth(), ofGetDay());
            saveSettings();
        }
    }
}

void Nippo::onMouseReleased(ofMouseEventArgs &mouse) {
    jobList->save();
}

bool Nippo::showFolderDialog() {
    bool valid = false;
    do {
        ofFileDialogResult r = ofSystemLoadDialog("ジョブデータのフォルダを選択してください", true);
        
        // キャンセルならfalseで終了
        if (!r.bSuccess) {
            return false;
        }
        
        ofDirectory d(r.getPath());
        if (d.isDirectory()) {
            // フォルダがあったらそれを読んで進む
            setDirectory(r.getPath());
            saveSettings();
            valid = true;
        }
        
        else {
            // フォルダを選択されていなかったら再度選択してもらう
            valid = false;
            ofSystemAlertDialog("ジョブデータのフォルダが選択されていません");
        }
    } while (!valid);
    
    // 成功して終了（キャンセルは早期returnされている）
    return true;
}

bool Nippo::loadSettings() {
    ofLogNotice("Nippo") << "Load " << directory;

    bool succeeded = false;
    
    // if setting file exists, load
    ofFile settingsFile = ofFile("settings.json");
    if (settingsFile.exists()) {
        ofJson settings = ofLoadJson(settingsFile);
        if (settings.count("directory") != 0) {
            setDirectory(settings["directory"]);
            succeeded = true;
        }
    }

    return succeeded;
}

bool Nippo::saveSettings() {
    ofJson settings;
    settings["directory"] = directory;
    ofSaveJson("settings.json", settings);
}

void Nippo::setDirectory(string path) {
    directory = path;
}

bool Nippo::loadJob(int year, int month, int date) {
    
}
