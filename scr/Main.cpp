#include <iostream>
#include "ScreenManager.h"

int main() {

	while (true) {
		ScreenManager::GetInstance().Update();
	}

	return 0;

}