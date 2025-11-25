#pragma once
#include "Character.h"
#include "CharacterFactory.h"


// プレイヤークラス
class Player : public Character {
public:
	Player(const CharacterData& arg_data, ObjectType type)
		:Character(arg_data,type)
	{
	}

	// 選択式の行動
	int ChoiceAction(std::shared_ptr<Character> arg_target) override;

};