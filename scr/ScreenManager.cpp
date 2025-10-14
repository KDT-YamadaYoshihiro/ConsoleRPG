#include "ScreenManager.h"

void ScreenManager::Update()
{
    if (currentScreen != nullptr) {
        currentScreen->Update();
    }
    else {
        std::cout << "currentScreen is nullptr" << std::endl;
    }
}

