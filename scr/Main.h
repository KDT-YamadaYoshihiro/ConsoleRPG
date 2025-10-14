#pragma once
#include <iostream>
#include "ScreenBase.h"

std::shared_ptr<Screen> screen = std::make_shared<Screen>();

int main() {

	while (true) {
		screen->Update();
		screen->Draw();
	}

	return 0;

}