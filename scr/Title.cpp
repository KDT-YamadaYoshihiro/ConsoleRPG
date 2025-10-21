#include "Title.h"
#include "Battle.h"
#include "ScreenManager.h"

void TitleScreen::Update()
{
	// エンターキーの入力を待つ
	std::cout << "Press Enter to Start" << std::endl;


	// スペースキーの入力後、スクリーンをステージへ遷移
	if (std::cin.get() == '\n') {
		ScreenManager::GetInstance().ChangeScreen<BattleScreen>();
		// スクリーンをクリアにする
		system("cls");
	}
}