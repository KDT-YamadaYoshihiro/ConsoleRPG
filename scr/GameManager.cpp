#include "GameManager.hpp"
#include"ScreenManager.h"

void GameManager::Run()
{
	while (m_running)
	{
		ScreenManager::GetInstance().Update();
	}
}
