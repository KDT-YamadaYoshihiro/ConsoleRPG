#include "ScreenManager.h"

void ScreenManager::Update()
{
	currentScreen->Update();
}

void ScreenManager::Draw()
{
	currentScreen->Draw();
}

template<typename T>
inline void ScreenManager::ChangeScreen(std::shared_ptr<T> newScreen)
{
	// スクリーンを変更
	currentScreen = newScreen;
}
