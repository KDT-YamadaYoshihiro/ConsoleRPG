#pragma once
#include <vector>
#include <memory>
#include "ScreenBase.h"
#include "CharacterFactory.h"
#include "Character.h"
#include "ObjectPool.h"
#include "view.h"


class BattleScreen : public ScreenBase {
public:
    // バトル進行ステート
    enum class State {
        Idle,           // バトル開始前、案内表示用
        PlayerTurn,     // プレイヤー行動フェーズ
        PTrurnEnd,      // プレイヤー終了フェーズ
        EnemyTurn,      // エネミー行動フェーズ
        ETurnEnd,       // エネミーの終了フェーズ
        CheckResult,    // 勝敗判定フェーズ
        FadeTransition, // フェード進行確認フェーズ
        Result          // バトル終了・リザルトへ
    };

    enum class Judg
    {
        None,
        Victory,
        Defeat,
    };

private:
    std::vector<std::shared_ptr<Character>> player;
    std::shared_ptr<view> battle_view;
    int enemyCount = 1;
    int currentPhase = 1;
    int baseEnemies = 1;  // 初期敵数
    State state = State::Idle;
    Judg judg = Judg::None;
    int DeadEnemies;

public:
    BattleScreen();

    void SetPlayer(std::vector<std::shared_ptr<Character>> p);

    void BattleStart();
    void Update() override;

private:
    void PlayerTurn();
    void EnemyTurn();
    void FadeTransition();
    bool Victoryjudg();
};
