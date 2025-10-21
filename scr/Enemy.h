#pragma once
#include "Character.h"
#include "CharacterFactory.h"

// エネミークラス
class Enemy : public Character {
public:
	Enemy(const CharacterData& arg_data)
		:Character(arg_data)
	{
		// Enemy specific initialization can be done here
	}

	// 行動選択
	// 疑似的AIで行動する(0-攻撃, 1-回復, 2-)
	int ChoiceAction(std::shared_ptr<Character> arg_target) override;
		

};
