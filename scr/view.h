#pragma once
#include <iostream>
#include <string>

class view {

public:

	// プレイヤー読み込みエラー
	void ErrPlayer() {
		std::cerr << "[Error] プレイヤーが存在しません!\n";
	}

	// スクリーン表示
	void ShowScreen() {
		std::cout << "\n=== Battle Screen ===\n";
	}

	// ステータスのメッセを表示
	void StateMsg()
	{
		std::cout << "---【ステータス】---" << std::endl;
	};

	// プレイヤーのステータス表示
	void PlayerState(std::string arg_name, int arg_lv, int arg_hp, int arg_atk,int arg_def)
	{
		std::cout << "プレイヤー\n" << "name:" << arg_name << "\nLv:" << arg_lv << "\nHP:" << arg_hp << "\nATK:" << arg_atk << "\nDEF:" << arg_def << "\n" << std::endl;
	};

	// エネミーのステータスを表示
	void EnemyState(std::string arg_name, int arg_lv, int arg_hp, int arg_atk, int arg_def)
	{
		std::cout << "エネミー\n" << "name:" << arg_name << "\nLv:" << arg_lv << "\nHP:" << arg_hp << "\nATK:" << arg_atk << "\nDEF:" << arg_def << "\n" << std::endl;

	};

	// バトル開始
	void StartBattle()
	{
		std::cout << "\n---【バトル開始】---" << std::endl;
	};

	// フェーズの表示
	void ShowPhase(int arg_phase)
	{
		std::cout << "\n=== フェーズ " << arg_phase << " 開始 ===\n";
	};

	// プレイヤーのターンメッセ
	void PlayerTurnMsg() 
	{
		std::cout << "\n--- プレイヤーのターン ---\n";
	};

	// エネミーのターンメッセ
	void EnemyTurnMsg()
	{
		std::cout << "\n--- エネミーのターン ---\n";
	};

	// 攻撃ダメージを表示
	void ShowDamage(std::string arg_attacker, std::string arg_target, int arg_damage)
	{
		std::cout <<arg_attacker << " は " << arg_target << " に " << arg_damage << " のダメージ！\n";
	};

	// 回復を表示
	void ShowHeal(std::string arg_name, int arg_hp, int arg_max_hp)
	{
		std::cout << arg_name << " は回復した！ HP:"<< arg_hp << "/" << arg_max_hp << "\n";
	};

	// 現状のHPを表示
	void ShowHp(std::string arg_name, int arg_hp)
	{
		std::cout << arg_name << "の残りHPは" << arg_hp << std::endl;;
	};

	// 選択の案内メッセ
	void ChoiceAnnounce() {
		std::cout << "行動を選択：1=攻撃 2=回復 >> ";
	}

	// 選択結果を表示
	void ChoiceMsg(int arg_choice)
	{
		if (arg_choice == 1) {
			std::cout << "\n攻撃が選択されました。\n";
		}
		else if(arg_choice == 2)
		{
			std::cout << "\n回復が選択されました。\n";
		}
	};

	// 討伐メッセ
	void DestroySmg(std::string arg_name) {
		std::cout << arg_name << " を倒した！\n";
	}

	// 無効入力時メッセ
	void ErrSmg()
	{
		std::cout << "無効な入力です。\nもう一度入力してください";
	};

	// 勝利時
	void WinSmg() 
	{
		std::cout << "\n敵は全滅した！勝利！\n";
	};

	// 敗北時
	void OverSmg()
	{
		std::cout << "\n味方は全滅した...敗北。\n";
	};

	// フェーズ進行メッセ
	void QuestionPhase()
	{
		std::cout << "\n次のフェーズに進みますか？(1:はい 2:いいえ) >> ";
	};

	// 画面一掃
	void viewClr() {
		system("cls");
	}

};