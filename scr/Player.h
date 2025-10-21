#pragma once
#include "Character.h"
#include "CharacterFactory.h"

// プレイヤークラス
class Player : public Character {
public:
	Player(const CharacterData& arg_data)
		:Character(arg_data)
	{
		// Player specific initialization can be done here
	}

	// 選択式の行動
	int ChoiceAction(std::shared_ptr<Character> arg_target) override;

};