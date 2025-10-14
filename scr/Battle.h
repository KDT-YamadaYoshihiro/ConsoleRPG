#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ScreenBase.h"
#include "Character.h"
#include "CharacterFactory.h"
#include "Enemy.h"

// バトル進行
enum class BATTLE_MODE {
	PLAYER_TURN,
	ENEMY_TURN,
	BATTLE_OVER
};

class Battle : public ScreenBase {

	// 戦闘に関するメンバ変数
	BATTLE_MODE battleMode;
	bool isBattleOver;

	// エネミーの生成（複数生成に対応）
	std::vector<std::shared_ptr<Character>> enemis;

	// プレイヤーを取得
	const std::vector<std::shared_ptr<Character>>& players = ScreenManager::GetInstance().GetPlayers();

public:

	// コンストラクタ
	Battle();

	// 更新処理
	void Update() override;
	// 描画処理
	void Draw() const override;


	// エネミーを生成する
	void GenerateEnemy(int arg_stageNumber);

	// 勝敗判定
	bool CheckVictory();

	// プレイヤーの行動選択
	void PlayerAction();

	// 敵の行動
	void EnemyAction();




};
