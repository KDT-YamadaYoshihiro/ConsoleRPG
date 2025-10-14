#pragma once
#include "ScreenBase.h"
#include "Character.h"
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

public:

	// コンストラクタ
	Battle();

	// 更新処理
	void Update() override;


	// エネミーを生成する
	void GenerateEnemy(int arg_stageNumber);

	// 勝敗判定
	bool CheckVictory();

	// プレイヤーの行動選択
	void PlayerAction();

	// 敵の行動
	void EnemyAction();




};
