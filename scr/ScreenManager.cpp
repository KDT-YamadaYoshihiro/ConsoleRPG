#include "ScreenManager.h"
#include "Title.h"
#include "CharacterFactory.h"

ScreenManager::ScreenManager()
{
	// 最初のスクリーンはタイトル
	if (currentScreen == nullptr) {
		currentScreen = std::make_shared<TitleScreen>();
	}
    InitPlayers();
    InitEnemyPool();
}

void ScreenManager::Update()
{
    if (currentScreen != nullptr) {
        currentScreen->Update();
    }
    else {
        std::cout << "currentScreen is nullptr" << std::endl;
    }
}

