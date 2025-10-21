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

	// デフォルトコンストラクタを明示的に定義
	Character() : data({ "", 0, 0, 0, 0, 0, 0 }) {}
	// コンストラクタ
	// 初期化
	Character(const CharacterData& arg_data)
		:data(arg_data)
	{

	};

	// ステータスの取得
	CharacterData GetData() const { return data; }
	std::string GetName() const { return data.name; }
	int GetID() const { return data.ID; }
	int GetLv() const { return data.Lv; }
	int GetHP() const { return data.HP; }
	int GetMaxHP() const { return data.maxHP; }
	int GetAttack() const { return data.attack; }
	int GetDefense() const { return data.defense; }
	int GetSpeed() const { return data.speed; }

	void setID(int id) { data.ID = id; }

	// ステータスを初期データで上書き
	void ResetFromData(const CharacterData& newData) {
		data = newData;  
	}
	// 行動
	virtual int ChoiceAction(std::shared_ptr<Character> arg_target) { return -1; }

	// ダメージを受ける
	void TakeDamage(int damage) {
		data.HP -= damage;
		if (data.HP < 0) {
			data.HP = 0;
		}
	}

	// 回復する
	void Heal() {
		data.HP += data.maxHP * 0.6;
		if (data.HP > data.maxHP) {
			data.HP = data.maxHP;
		}
	}
	// 全回復
	void ResetHP() {
		data.HP = data.maxHP;
	}

	// 生存確認
	bool IsAlive() const {
		
		if (data.HP < 1) {
			return true;
		}
		else {
			return false;
		}
	}

	void LvUp() {
		data.Lv++;
		data.maxHP *= 1.1;
		data.attack *= 1.1;
		data.defense *= 1.1;
		data.speed *= 1.1;
	}

};