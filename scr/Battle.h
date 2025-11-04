#pragma once
#include <vector>
#include <memory>
#include "ScreenBase.h"
#include "CharacterFactory.h"
#include "Character.h"
#include "ObjectPool.h"
#include "Calculation.h"


class BattleScreen : public ScreenBase {

private:
    std::vector<std::shared_ptr<Character>> player;
    std::shared_ptr<view> battle_view;
    int enemyCount = -1;
    int currentPhase = -1;
    int baseEnemies = -1;  // 初期敵数
    State state = State::Idle;
    Judg judg = Judg::None;
    int DeadEnemies;
	std::shared_ptr<Calculation> calc;

public:
	// コンストラクタ
    BattleScreen();
    // 初期化
    void BattleStart();
	// 更新処理
    void Update() override;

private:
	// プレイヤー行動
    void PlayerTurn();
	// プレイヤーの選択肢取得
	int GetPlayerAction();
	// プレイヤー攻撃
	void PlayerAttack();
	// プレイヤー回復
	void PlayerHeal();

	// エネミー行動
    void EnemyTurn();
	// フェード切り替え
    void FadeTransition();
	// 勝敗判定
    bool Victoryjudg();
};
