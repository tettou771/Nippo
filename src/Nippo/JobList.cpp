#include "JobList.h"

JobList::JobList(){
    
}

void JobList::onStart(){
    weeks.push_back("日");
    weeks.push_back("月");
    weeks.push_back("火");
    weeks.push_back("水");
    weeks.push_back("木");
    weeks.push_back("金");
    weeks.push_back("土");
    
    setWidth(ofGetWidth());
    setHeight(ofGetHeight());
}

void JobList::onDraw() {
    // 今日の日付
    stringstream daystr;
    string week = weeks[ofGetWeekday()];
    daystr << year << "年 " << month << "月 " << date << "日 (" << week << ")";
    auto daystrrect = Job::font.getStringBoundingBox(daystr.str(), 0, 0);
    ofSetColor(100);
    Job::font.drawString(daystr.str(), (getWidth() - daystrrect.width) / 2, 4 + daystrrect.height);
    
    bool debug = false;
    if (debug) {
        ofPushMatrix();
        ofTranslate(500, 20);
        
        for (int i=0; i<data.getNumRows(); ++i) {
            auto &row = data.getRow(i);
            stringstream ss;
            ss << ofToString(i) + " ";
            for (int j=0; j<row.getNumCols(); ++j) {
                ss << " " << row.getString(j);
            }
            ofDrawBitmapString(ss.str(), 0, 0);
            ofTranslate(0, 20);
        }
        ofPopMatrix();
    }
}

void JobList::onKeyPressed(ofKeyEventArgs &key) {
    if (key.key == OF_KEY_RETURN) {
        showNewJobDialog();
    }
}

string JobList::toPath(string dir, int year) {
    stringstream path;
    path << dir;
    if (dir.substr(dir.length() - 1,1) != "/") path << "/";
    path << ofToString(year, 4, '0');
    path << ".csv";
    return path.str();
}

void JobList::showNewJobDialog() {
    auto result = ofSystemTextBoxDialog("新しいジョブの名前を入力してください");
    if (result.length() > 1) {
        // ジョブを追加する
        auto newJob = make_shared<Job>(result);
        ofAddListener(newJob->memoChangedEvents, this, &JobList::memoChanged);
        jobs.insert(jobs.begin(), newJob);
        updateJobPositions();
        addChild(newJob);
    }
    
    string newJobName = "";
}

void JobList::hoursChanged() {
    save();
}

void JobList::memoChanged() {
    updateJobPositions();
    // メモが書き変わったので保存
    save();
}

void JobList::updateJobPositions() {
    ofVec2f jobPos(10, 50);
    for (auto j : jobs) {
        j->setPos(jobPos);
        jobPos.y += j->getHeight();
    }
}

void JobList::load(string dir, int year, int month, int date) {
    string filePath = toPath(dir, year);
    ofLogNotice("JobList") << "Load job file " << filePath;
    
    data.load(filePath);
    this->directory = dir;
    this->year = year;
    this->month = month;
    this->date = date;
    
    // 一旦全てのジョブを破棄
    for (auto job : jobs) {
        job->destroy();
    }
    jobs.clear();
    
    // ジョブをリストアップ
    // 新しいジョブを上に持ってくるため、逆順でスキャンする
    for (int i=data.getNumRows() - 1; i>=0; --i) {
        auto row = data.getRow(i);
        
        // 1列目は日時 2023/01/02 という形式
        string dateStr = row.getString(0);
        auto splited = ofSplitString(dateStr, "/");
        
        // 日付が合致するかどうか
        bool isToday = false;
        if (splited.size() == 3) {
            int rowYear = ofToInt(splited[0]);
            int rowMonth = ofToInt(splited[1]);
            int rowDate = ofToInt(splited[2]);
            
            // 日付を判定
            if (rowYear == year && rowMonth == month && rowDate == date) {
                isToday = true;
            }
        }
        // 2列目がジョブの名前
        string jobName = row.getString(1);
        // 3列目がジョブの累計時間
        // ただし、内部的にはdeciHoursの単位なので、10倍して加算しなければならない
        int jobDeciHours = round(row.getFloat(2) * 10);
        
        // 4列目がメモ欄
        string jobMemo = row.getString(3);
        
        // すでにジョブリストにあるかどうか確認
        bool jobExists = false;
        for (auto j : jobs) {
            if (j->name == jobName) {
                jobExists = true;
                // 今日なら
                // そのジョブにdeciHoursを加算,メモ追加
                if (isToday) {
                    j->addCount(jobDeciHours);
                    j->addMemo(jobMemo);
                }
                
                break;
            }
        }
        
        // なければジョブを追加
        if (!jobExists) {
            shared_ptr<Job> newJob = make_shared<Job>(jobName);
            ofAddListener(newJob->memoChangedEvents, this, &JobList::memoChanged);
            
            // 今日ならそのジョブにdeciHoursを加算,メモ追加
            if (isToday) {
                newJob->addCount(jobDeciHours);
                newJob->addMemo(jobMemo);
            }
            
            addChild(newJob);
            jobs.push_back(newJob);
        }
    }
    
    updateJobPositions();
}

void JobList::save() {
    string path = toPath(directory, year);
    ofLogNotice("JobList") << "Save to " << path;
    
    // セーブするjobのリスト
    vector<shared_ptr<Job> > toSaveJobs;
    for (auto j : jobs) {
        toSaveJobs.push_back(j);
    }

    // 今日のデータに数値を加算して更新
    for (int i=0; i<data.getNumRows(); ++i) {
        auto &row = data.getRow(i);
        
        // 1列目は日時 2023/01/02 という形式
        string dateStr = row.getString(0);
        auto splited = ofSplitString(dateStr, "/");
        
        // 日付が合致するかどうか
        bool isToday = false;
        if (splited.size() == 3) {
            int rowYear = ofToInt(splited[0]);
            int rowMonth = ofToInt(splited[1]);
            int rowDate = ofToInt(splited[2]);
            
            // 日付を判定
            if (rowYear == year && rowMonth == month && rowDate == date) {
                isToday = true;
            }
        }
        
        // 今日のデータ以外は触らない
        if (!isToday) continue;
                
        // 2列目がジョブの名前
        string jobName = row.getString(1);
        // 該当するジョブを探す
        shared_ptr<Job> job = nullptr;
        for (int ji = 0; ji < toSaveJobs.size(); ++ji) {
            auto j = toSaveJobs[ji];
            if (j->name == jobName) {
                job = j;
                
                // toSaveJobsから削除
                toSaveJobs.erase(toSaveJobs.begin() + ji);
                break;
            }
        }
        
        // あるはずだが、もしjobsに該当項目がなければスキップ
        if (job == nullptr) {
            ofLogWarning("JobList") << "Job " << jobName << " is not found in jobs";
            continue;
        }
        
        // 3列目がジョブの累計時間
        // ただし、内部的にはdeciHoursの単位なので、10分の1して加算しなければならない
        
        row.setFloat(2, job->getHours());
        
        // 4列目がmemo
        row.setString(3, job->getMemo());
    }
    
    // もしtoSaveJobsに残っているjobがあったら、新規ジョブとして追加
    for (auto j : toSaveJobs) {
        // ただし0時間かつmemoがないものは無視
        if (j->deciHours == 0 && j->getMemo() == "") continue;
        
        ofxCsvRow newRow;
        string todayString = ofToString(ofGetYear(), 4, '0')
        + '/' + ofToString(ofGetMonth(), 2, '0')
        + '/' + ofToString(ofGetDay(), 2, '0');
        newRow.setString(0, todayString);
        newRow.setString(1, j->name);
        newRow.setFloat(2, j->getHours());
        data.addRow(newRow);
    }
    
    data.save(toPath(directory, year));
}
