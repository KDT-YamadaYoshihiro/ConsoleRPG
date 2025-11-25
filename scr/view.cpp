#include "view.h"
#include "Enum.h"
#include <string>

// マネージャー用エラーメッセージ
void view::ErrManager()
{
	std::cerr << "[Error] スクリーンが存在しません!\n";
}
// タイトル画面表示
void view::TitleScreen()
{
	std::cout << "\n=== Title Screen ===\n";
	std::cout << "Press Enter to Start" << std::endl;
}
// プレイヤー読み込みエラー
void view::ErrPlayer()
{
	std::cerr << "[Error] プレイヤーが存在しません!\n";
}
// スクリーン表示
void view::ShowScreen()
{
	std::cout << "\n=== Battle Screen ===\n";
}
// ステータスのメッセを表示
void view::StateMsg()
{
	std::cout << "---【ステータス】---" << std::endl;
}

/*
*	ひとつずつ渡すのやめよう
*/

// プレイヤーのステータス表示
void view::PlayerState(std::string arg_name, int arg_lv, int arg_hp, int arg_atk, int arg_def)
{
	std::cout << "プレイヤー\n" << "name:" << arg_name << "\nLv:" << arg_lv << "\nHP:" << arg_hp << "\nATK:" << arg_atk << "\nDEF:" << arg_def << "\n" << std::endl;
}
// エネミーのステータスを表示
void view::EnemyState(std::string arg_name, int arg_lv, int arg_hp, int arg_atk, int arg_def)
{
	std::cout << "エネミー\n" << "name:" << arg_name << "\nLv:" << arg_lv << "\nHP:" << arg_hp << "\nATK:" << arg_atk << "\nDEF:" << arg_def << "\n" << std::endl;
}


/// <summary>
///	キャラクターステータス出力
/// </summary>
/// <param name="data"></param>
void view::DispCharaStatus(ObjectType type , const CharacterData& data)
{
	//	一時的に
	std::string str;

	switch (type)
	{
	case ObjectType::Player:
		str = "プレイヤー";
		break;
	case ObjectType::Enemy:
		str = "エネミー";
		break;
	default:
		break;
	}

	std::cout << str << std::endl<<
		"name:" << data.name << "\nLv:" << data.Lv << "\nHP:" << data.HP << "\nATK:" << data.attack << "\nDEF:" << data.defense << "\n" << std::endl;
}



// バトル開始
void view::StartBattle()
{
	std::cout << "\n---【バトル開始】---" << std::endl;
}
// フェーズの表示
void view::ShowPhase(int arg_phase)
{
	std::cout << "\n=== フェーズ " << arg_phase << " 開始 ===\n";
}
// プレイヤーのターンメッセ
void view::PlayerTurnMsg()
{
	std::cout << "\n\033[01m --- プレイヤーのターン --- \033[m \n";
}
// エネミーのターンメッセ
void view::EnemyTurnMsg()
{
	std::cout << "\n\033[01m --- エネミーのターン --- \033[m \n";
}
// 攻撃ダメージを表示
void view::ShowDamage(std::string arg_attacker, std::string arg_target, int arg_damage)
{
	std::cout << arg_attacker << " は " << arg_target << " に\033[31m " << arg_damage << " のダメージ！ \033[m \n";
}
// 回復を表示
void view::ShowHeal(std::string arg_name, int arg_hp, int arg_max_hp)
{
	std::cout << arg_name << "は\033[32m 回復した！ \033[m HP:" << arg_hp << "/" << arg_max_hp << "\n";
}
// 現状のHPを表示
void view::ShowHp(std::string arg_name, int arg_hp)
{
	std::cout << arg_name << "の残りHPは" << arg_hp << std::endl;;
}
// 選択の案内メッセ
void view::ChoiceAnnounce()
{
	std::cout << "行動を選択：1=攻撃 2=回復 >> ";
}
// 選択結果を表示
void view::ChoiceMsg(int arg_choice)
{
	if (arg_choice == ATTACK) {
		std::cout << "\n攻撃が選択されました。\n";
	}
	else if (arg_choice == HEAL)
	{
		std::cout << "\n回復が選択されました。\n";
	}
}
// 討伐メッセ
void view::DestroySmg(std::string arg_name)
{
	std::cout << arg_name << " を倒した！\n";
}
// 無効入力時メッセ
void view::ErrSmg()
{
	std::cout << "無効な入力です。\nもう一度入力してください";
}
// 勝利時
void view::WinSmg()
{
	std::cout << "\n敵は全滅した！勝利！\n";
}
// 敗北時
void view::OverSmg()
{
	std::cout << "\n味方は全滅した...敗北。\n";
}
// フェーズ進行メッセ
void view::QuestionPhase()
{
	std::cout << "\n次のフェーズに進みますか？(1:はい 2:いいえ) >> ";
}
// 画面一掃
void view::viewClr()
{
	system("cls");
}
// リザルト画面表示
void view::ResultScreen(int arg_fade, std::shared_ptr<Character> arg_character)
{
	std::cout << "\n=== Result Screen ===\n";
	// リザルト表示
	std::cout << "Last Fade: " << arg_fade << "\n";
	std::cout << "Player: " << arg_character->GetName() << "\n";
	std::cout << "LV: " << arg_character->GetLv()
		<< " HP: " << arg_character->GetHP() << "/" << arg_character->GetMaxHP()
		<< " ATK: " << arg_character->GetAttack()
		<< " DEF: " << arg_character->GetDefense() << "\n";

	std::cout << "1: Retry\n2: Exit\n";
}
// 再挑戦メッセ
void view::RetryMsg()
{
	std::cout << "Restarting battle...\n";
}
// 終了メッセ
void view::ExitMsg()
{
	std::cout << "Exiting game...\n";

}
