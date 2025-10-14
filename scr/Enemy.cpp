#include "Enemy.h"
#include <iostream>

int Enemy::ChooseAction(std::shared_ptr<Character> arg_target)
{
	// ŠÈ’P‚È‹^Ž—AI‚Ì—á
	if (data.HP < data.maxHP / 4) {
		// HP‚ª25%ˆÈ‰º‚È‚ç‰ñ•œ‚ð‘I‘ð
		return 1; // ‰ñ•œ
	}
	else {
		// ‚»‚êˆÈŠO‚ÍUŒ‚‚ð‘I‘ð
		return 0; // UŒ‚
	}
}
