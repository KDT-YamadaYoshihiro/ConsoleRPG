#include "CharacterFactory.h"

// キャラクターデータテーブルの定義
const CharacterData CharacterFactory::CharacterTable[] = {
	// プレイヤー
	{"Akira", AKIRA, 1, 100, 100, 20, 10, 15},
	{"El", EL, 1, 80, 80, 25, 5, 20},
	{"Alia", ALIA, 1, 90, 90, 15, 15, 10},
	{"Pino", PINO, 1, 70, 70, 30, 3, 25},
	// エネミー
	{"Slime", SLIME, 1, 50, 50, 20, 5, 5},
	{"Goblin", GOBLIN, 1, 60, 60, 15, 10, 10},
	{"Wolf", WOLF, 1, 80, 80, 20, 8, 15},
};

const CharacterData* CharacterFactory::GetCharacterData(int id) const
{
	for (const auto& data : CharacterTable) {
		if (data.ID == id) {
			return &data;
		}
	}
	return nullptr; // 見つからない場合
}

std::shared_ptr<Character> CharacterFactory::CreateCracter(int arg_id)
{
	// IDが範囲内であることを確認
	if (CharacterTable[arg_id].ID == arg_id) {
		// IDが見つかった場合はそのデータを使ってCharacterオブジェクトを生成して返す
		return std::make_shared<Character>(CharacterTable[arg_id]);
	}

	// IDが見つからなかった場合はnullptrを返す
	return nullptr;
}
