#pragma once
#include "ScreenBase.h"
#include "Character.h"
#include "CharacterFactory.h"

class ScreenManager; // 前方宣言

class ResultScreen : public ScreenBase {
private:

	// 最終フェード数
    int lastFade = START_FADE;
	// プレイヤー情報
    std::vector<std::shared_ptr<Character>> player;
	// 表示済みフラグ
    bool displayed = false;

public:

	// コンストラクタ
    ResultScreen();

	// 最終フェード数セット関数
    void SetLastFade(int fade);

    // ScreenBase の Update をオーバーライド
    void Update() override;
};
