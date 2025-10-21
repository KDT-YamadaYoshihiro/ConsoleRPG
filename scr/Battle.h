#pragma once
#include <vector>
#include <memory>
#include "ScreenBase.h"
#include "CharacterFactory.h"
#include "Character.h"
#include "ObjectPool.h"

class BattleScreen : public ScreenBase {
public:
    // バトル進行ステート
    enum class State {
        Idle,           // バトル開始前、案内表示用
        PlayerTurn,     // プレイヤー行動フェーズ
        EnemyTurn,      // エネミー行動フェーズ
        CheckResult,    // 勝敗判定フェーズ
        FadeTransition, // フェード進行確認フェーズ
        Result          // バトル終了・リザルトへ
    };

private:
    std::vector<std::shared_ptr<Character>> player;
    std::vector<std::shared_ptr<Character>> enemies;
    ObjectPool<Character> enemyPool;

    int currentFade = 1;
    int baseEnemies = 1;  // 初期敵数
    State state = State::Idle;

    int DeadEnemies;

public:
    BattleScreen();

    void SetPlayer(std::vector<std::shared_ptr<Character>> p);

    void BattleStart();
    void Update() override;

private:
    void PlayerTurn();
    void EnemyTurn();
    bool AllEnemiesDead() const;
    int ChooseEnemyID() const;
};
