#include "Global.h"

ofTrueTypeFont Global::fontMain, Global::fontSmall, Global::fontNumber;
bool Global::prepared = false;

void Global::prepare() {
    // メインのフォント
    // 日本語が必要なので、settingsを使ってJapaneseを追加した上でロード
    int fontSize = listHeight * 0.6;
#ifdef TARGET_OS_MAC
    ofTrueTypeFontSettings settings("ヒラギノ角ゴシック", fontSize);
#else
    ofTrueTypeFontSettings settings(OF_TTF_SANS, fontSize);
#endif
    settings.addRanges(ofAlphabet::Latin);
    settings.addRanges(ofAlphabet::Japanese);
    fontMain.load(settings);
    
    // メモ用のフォント 小さくしてロードする
    settings.fontSize = 10;
    fontSmall.load(settings);
    
    // カウンターの数字のフォント
    fontSize = listHeight * 0.6;
    fontNumber.load(OF_TTF_SANS, fontSize);

    prepared = true;
}
