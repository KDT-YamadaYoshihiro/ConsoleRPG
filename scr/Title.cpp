#include "Title.h"
#include "Stage.h"
#include "ScreenManager.h"

void Title::Update()
{
	// エンターキーの入力を待つ
	std::cout << "Press Enter to Start" << std::endl;


	// スペースキーの入力後、スクリーンをステージへ遷移
	if (std::cin.get() == '\n') {
		ScreenManager::GetInstance().ChangeScreen(std::shared_ptr<Stage>());
		// スクリーンをクリアにする
		system("cls");
	}
}