#pragma once
#include "ScreenBase.h"
#include "Character.h"
#include "CharacterFactory.h"

class ScreenManager; // 前方宣言

class ResultScreen : public ScreenBase {
private:
    int lastFade = 0;
    std::vector<std::shared_ptr<Character>> player;
    bool displayed = false;

public:
    ResultScreen();

    void SetPlayer(std::vector<std::shared_ptr<Character>> p);
    void SetLastFade(int fade);

    // ScreenBase の Update をオーバーライド
    void Update() override;
};
