#pragma once
#include <string>

struct CharacterData
{
	std::string name;
	int ID;
	int maxHP;
	int HP;
	int attack;
	int defense;
	int speed;

};

enum CHARA_NAME{
	// プレイヤー
	AKIRA,
	EL,
	ALIA,
	PINO,

	// エネミー
	SLIME,
	GOBLIN,
	WOLF,
	DRAGON,

	// キャラクターMax値
	CHARA_MAX
};

