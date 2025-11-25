#pragma once

#include <stdint.h>

// 行動選択肢
enum ACTION {
	SELECT,
	ATTACK,
	HEAL,
	END,
	NONE
};

// ゲーム終了選択肢
enum GAME_END {
	RETRY = 1,
	EXIT = 2,
};

// フェーズ選択肢
enum CONTINUECHOICE {
	NEXT_PHASE = 1,
	TO_RESULT = 2,
};

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

// 勝敗判定
enum class Judg {
    None,
    Victory,
    Defeat,
};

//  オブジェクト
enum class ObjectType:uint32_t
{
    None,
    Player,
    Enemy,
};