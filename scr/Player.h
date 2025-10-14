#pragma once
#include "Character.h"
#include "CharacterFactory.h"

class Player : public Character {
public:
	Player(const CharacterData& arg_data)
		:Character(arg_data)
	{
		// Player specific initialization can be done here
	}

	// ‘I‘ğ®‚Ìs“®
	int ChooseAction(std::shared_ptr<Character> arg_target) override;

};