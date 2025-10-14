#pragma once
#include "CharacterData.h"
#include "Character.h"
#include <memory>

class CharacterFactory {

	static const CharacterData CharacterTable[];

	// コンストラクタ
	CharacterFactory() = default;

public:

	// コピー禁止
	CharacterFactory(const CharacterFactory&) = delete;
	// 代入禁止
	CharacterFactory& operator=(const CharacterFactory&) = delete;
	// シングルトンインスタンス取得
	static CharacterFactory& GetInstance()
	{
		static CharacterFactory instance;
		return instance;
	}

	// 指定したIDのキャラクターデータを生成して返す
	std::shared_ptr<Character> CreateCracter(int arg_id);

	

};