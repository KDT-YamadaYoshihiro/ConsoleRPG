#include <iostream>
#include "ScreenManager.h"

#include"GameManager.hpp"


int main() {
	GameManager& game = GameManager::Instace();
	int result = 0;

	game.Run();
	result = game.Shutdown();

	return result;
}