#include "Player.h"
#include <iostream>

int Player::ChoiceAction(std::shared_ptr<Character> arg_target)  {

	int act = -1;
	// 行動選択のメニューを表示
	switch (action)
	{
	case ACTION::SELECT:

		break;
	case ACTION::ATTACK:

		arg_target->TakeDamage(this->data.attack);

		action = ACTION::END;

		break;
	case ACTION::HEAL:

		this->Heal(); // 固定値で回復

		action = ACTION::END;

		break;

	case ACTION::END:

		return 0;

		break;

	case ACTION::NONE:
		break;
	default:
		break;
	}

}