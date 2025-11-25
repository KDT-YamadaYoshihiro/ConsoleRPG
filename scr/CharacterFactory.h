#pragma once
#include "CharacterData.h"
#include "Character.h"
#include <unordered_map>


class CharacterFactory {

	static const CharacterData CharacterTable[];

	std::unordered_map<int, CharacterData> m_charaterTable;


	// コンストラクタ
	CharacterFactory();
	virtual ~CharacterFactory() = default;

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

	// 指定IDのキャラクターデータを取得
	const CharacterData* GetCharacterData(int id) const;

	// 指定したIDのキャラクターデータを生成して返す
	std::shared_ptr<Character> CreateCracter(int arg_id,ObjectType type);
};