#include "JobList.h"

JobList::JobList(){
    
}

void JobList::onStart(){
    header.setString(0, "day");
    header.setString(1, "job");
    header.setString(2, "hours");
    header.setString(3, "memo");
}

void JobList::onDraw() {
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
    int jobPos = 0;
    int margin = 5;
    for (auto j : jobs) {
        j->setPos(0, jobPos);
        jobPos += j->getHeight() + margin;
    }
}

void JobList::setDirectory(string dir) {
    directory = dir;
}

void JobList::load(int year, int month, int day) {
    string filePath = toPath(directory, year);
    ofLogNotice("JobList") << "Load job file " << filePath;
    
    data.load(filePath);
    this->year = year;
    this->month = month;
    this->day = day;
    
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
            if (rowYear == year && rowMonth == month && rowDate == day) {
                isToday = true;
            }
        }
        // 日付ではない場合はスキップ（ヘッダ行）
        else {
            continue;
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
    
    // ヘッダ行がなければつける
    if (data.getRow(0).getString(0) != header.getString(0)) {
        data.insertRow(0, header);
    }
    
    updateJobPositions();
    
    // 日付変更イベント
    DayChangedEventArgs args(year, month, day);
    ofNotifyEvent(dayChangedEvent, args);
}

void JobList::loadToday() {
    weekday = ofGetWeekday();
    load(ofGetYear(), ofGetMonth(), ofGetDay());
}

void JobList::loadPreviousDay(){
    day--;
    if (day == 0) {
        month--;
        if (month == 0) {
            year--;
            month = 12;
        }
        switch (month) {
            case 2:
                if (isUruuDoshi(year)) day = 29;
                else day = 28;
                break;
            case 4:case 6:case 9:case 11:
                day = 30;
                break;
            default:
                day = 31;
                break;
        }
    }

    weekday--;
    if (weekday == 0) weekday = 6;

    load(year, month, day);
}

void JobList::loadNextDay(){
    int maxDay = 31;
    switch (month) {
        case 2:
            if (isUruuDoshi(year)) maxDay = 29;
            else maxDay = 28;
            break;
        case 4:case 6:case 9:case 11:
            maxDay = 30;
            break;
        default:
            maxDay = 31;
            break;
    }
    
    day++;
    if (day > maxDay) {
        month++;
        if (month > 12) year++;
    }
    
    weekday++;
    if (weekday == 6) weekday = 0;
    
    load(year, month, day);
    
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
            if (rowYear == year && rowMonth == month && rowDate == day) {
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

bool JobList::isUruuDoshi(int y){
    return y%4==0 && (y%100!=0 || y%400==0);
}
