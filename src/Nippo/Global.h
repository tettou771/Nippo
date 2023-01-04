#pragma once
#include "ofMain.h"

class Global {
    Global(){;}
public:
    static void prepare();
    static ofTrueTypeFont fontMain, fontSmall, fontNumber;
    static const int listHeight = 24;
    
private:
    static bool prepared;
};
