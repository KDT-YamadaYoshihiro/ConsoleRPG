#include "Title.h"
#include "Battle.h"
#include "ScreenManager.h"

TitleScreen::TitleScreen()
{
	// ビュークラスの生成
	screen_view = std::make_shared<view>();
}

// 更新処理
void TitleScreen::Update()
{
	screen_view->TitleScreen();

	// スペースキーの入力後、スクリーンをステージへ遷移
	if (std::cin.get() == '\n') {
		ScreenManager::GetInstance().ChangeScreen<BattleScreen>();
		// スクリーンをクリアにする
		screen_view->viewClr();
	}
}