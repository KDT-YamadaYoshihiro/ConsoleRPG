#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "Character.h"

class view {

private:
	view() = default;
	virtual ~view() = default;

public:
	view(const view&) = delete;
	view& operator=(const view&) = delete;

	static view& Instance()
	{
		static view instance;
		return instance;
	}

	// マネージャー用エラーメッセージ
	void ErrManager();
	// タイトル画面表示
	void TitleScreen();
	// プレイヤー読み込みエラー
	void ErrPlayer();
	// スクリーン表示
	void ShowScreen();
	// ステータスのメッセを表示
	void StateMsg();
	// プレイヤーのステータス表示
	void PlayerState(std::string arg_name, int arg_lv, int arg_hp, int arg_atk, int arg_def);
	// エネミーのステータスを表示
	void EnemyState(std::string arg_name, int arg_lv, int arg_hp, int arg_atk, int arg_def);


	void DispCharaStatus(ObjectType type, const CharacterData& data);
	

	// バトル開始
	void StartBattle();
	// フェーズの表示
	void ShowPhase(int arg_phase);
	// プレイヤーのターンメッセ
	void PlayerTurnMsg();
	// エネミーのターンメッセ
	void EnemyTurnMsg();
	// 攻撃ダメージを表示
	void ShowDamage(std::string arg_attacker, std::string arg_target, int arg_damage);
	// 回復を表示
	void ShowHeal(std::string arg_name, int arg_hp, int arg_max_hp);
	// 現状のHPを表示
	void ShowHp(std::string arg_name, int arg_hp);
	// 選択の案内メッセ
	void ChoiceAnnounce();
	// 選択結果を表示
	void ChoiceMsg(int arg_choice);
	// 討伐メッセ
	void DestroySmg(std::string arg_name);
	// 無効入力時メッセ
	void ErrSmg();
	// 勝利時
	void WinSmg();
	// 敗北時
	void OverSmg();
	// フェーズ進行メッセ
	void QuestionPhase();
	// 画面一掃
	void viewClr();
	// リザルト画面表示
	void ResultScreen(int arg_fade, std::shared_ptr<Character> arg_character);
	// 再挑戦メッセ
	void RetryMsg();
	// 終了メッセ
	void ExitMsg();
};