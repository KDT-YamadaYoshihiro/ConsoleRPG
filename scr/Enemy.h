#pragma once
#include "Character.h"
#include "CharacterFactory.h"

// エネミークラス
class Enemy : public Character {
public:

	Enemy() = default;
	Enemy(const CharacterData& arg_data,ObjectType type)
		:Character(arg_data,type)
	{
	}

	// 行動選択
	// 疑似的AIで行動する(0-攻撃, 1-回復, 2-)
	int ChoiceAction(std::shared_ptr<Character> arg_target) override;
	void SetData(const CharacterData& arg_data) { data = arg_data; }

};
