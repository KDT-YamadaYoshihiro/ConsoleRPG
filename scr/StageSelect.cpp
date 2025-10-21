#include "StageSelect.h"
#include <iostream>

void StageSelectScreen::Init() {
    std::cout << "=== ステージ選択 ===\n";
}

void StageSelectScreen::Update() {
    std::cout << "ステージ1を選択しました。\n";
    endFlag = true;
}
