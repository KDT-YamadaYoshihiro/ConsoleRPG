#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// キャラクターデータ構造体
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

// キャラクター名の列挙型
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

