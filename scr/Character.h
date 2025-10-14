#pragma once
#include "CharacterData.h"

// 行動選択の列挙型
enum class ACTION {
	SELECT,
	ATTACK,
	HEAL,
	END,
	NONE
};

// キャラクターの基底クラス
class Character {

protected:

	// キャラクターデータ
	CharacterData data;
	// 行動選択
	ACTION action = ACTION::NONE;


public:

	// コンストラクタ
	// 初期化
	Character(const CharacterData& arg_data)
		:data(arg_data)
	{

	};

	// キャラクターの情報を表示
	void ShowStatus() const {
		std::cout << "Name: " << data.name << std::endl;
		std::cout << "ID: " << data.ID << std::endl;
		std::cout << "HP: " << data.HP << "/" << data.maxHP << std::endl;
		std::cout << "Attack: " << data.attack << std::endl;
		std::cout << "Defense: " << data.defense << std::endl;
		std::cout << "Speed: " << data.speed << std::endl;
	}

	// ステータスの取得
	std::string GetName() const { return data.name; }
	int GetID() const { return data.ID; }
	int GetHP() const { return data.HP; }
	int GetMaxHP() const { return data.maxHP; }
	int GetAttack() const { return data.attack; }
	int GetDefense() const { return data.defense; }
	int GetSpeed() const { return data.speed; }

	// 行動
	virtual int ChooseAction(std::shared_ptr<Character> arg_target) { return -1; }

	// ダメージを受ける
	void TakeDamage(int damage) {
		data.HP -= damage;
		if (data.HP < 0) {
			data.HP = 0;
		}
	}

	// 回復する
	void Heal(int amount) {
		data.HP += amount;
		if (data.HP > data.maxHP) {
			data.HP = data.maxHP;
		}
	}

	// 生存確認
	bool IsAlive() const {
		return data.HP > 0;
	}

};