#include "ScreenManager.h"
#include "Title.h"
#include "CharacterFactory.h"

ScreenManager::ScreenManager()
    :slimePool(MAX_POOL)
{
	// ビュークラスの生成
	manager_view = std::make_shared<view>();
	// 最初のスクリーンはタイトル
	if (currentScreen == nullptr) {
		currentScreen = std::make_shared<TitleScreen>();
	}
    InitPlayers();
}

// 更新処理
void ScreenManager::Update()
{
	// 現在のスクリーンの更新処理を呼び出す
    if (currentScreen != nullptr) {
        currentScreen->Update();
    }
    else {
        // エラー表示
        manager_view->ErrManager();
    }
}

