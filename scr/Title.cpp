#include "Title.h"
#include "Battle.h"
#include "ScreenManager.h"

TitleScreen::TitleScreen()
{
}

// 更新処理
void TitleScreen::Update()
{
	view::Instance().TitleScreen();

	// スペースキーの入力後、スクリーンをステージへ遷移
	if (std::cin.get() == '\n') {
		ScreenManager::GetInstance().ChangeScreen<BattleScreen>();
		// スクリーンをクリアにする
		view::Instance().viewClr();
	}
}