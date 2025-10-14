#include "Player.h"
#include <iostream>

int Player::ChooseAction(std::shared_ptr<Character> arg_target)  {

	int act = -1;
	// 行動選択のメニューを表示
	switch (action)
	{
	case ACTION::SELECT:

		// 攻撃か回復か選択
		std::cout << "行動を選択してください\n";
		std::cout << "0: 攻撃\n"<< "1: 回復";
		std::cin >> act;

		// 入力の妥当性を確認
		while (act < 0 || act > 1) {
			std::cout << "無効な選択です。もう一度入力してください。\n";
			std::cin >> act;
		}

		if (act == 0) {
			action = ACTION::ATTACK;
		}
		else if (act == 1) {
			action = ACTION::HEAL;
		}

		break;
	case ACTION::ATTACK:

		arg_target->TakeDamage(this->data.attack);

		action = ACTION::END;

		break;
	case ACTION::HEAL:

		this->Heal(20); // 固定値で回復

		action = ACTION::END;

		break;

	case ACTION::END:

		return;

		break;

	case ACTION::NONE:
		break;
	default:
		break;
	}

}