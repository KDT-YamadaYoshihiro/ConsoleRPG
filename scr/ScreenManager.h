#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "ScreenBase.h"
#include "Battle.h"

#include "Character.h"
#include "CharacterFactory.h"
#include "PoolManager.h"

class ScreenManager {

	// ステージ番号
	int stageNumber = 0;

	std::vector<std::shared_ptr<Character>> players;
	std::vector<int> enemyIDs;

	std::shared_ptr<ScreenBase> currentScreen = nullptr;


	// コンストラクタ
	//　初期化
	ScreenManager();
	// デストラクタ
	~ScreenManager() = default;


public:

	// コピー禁止
	ScreenManager(const ScreenManager&) = delete;
	// 代入禁止
	ScreenManager& operator=(const ScreenManager&) = delete;
	// シングルトンインスタンス取得
	static ScreenManager& GetInstance()
	{
		static ScreenManager instance;
		return instance;
	}

	// プレイヤーを生成してプールに登録
	void InitPlayers() {
		auto akira = CharacterFactory::GetInstance().CreateCracter(AKIRA);
		if (!akira) throw std::runtime_error("アキラの生成に失敗しました");
		players.push_back(akira);
	}

	// 敵キャラプールの初期化
	void InitEnemyPool() {
		enemyIDs = { SLIME, GOBLIN, WOLF }; // 敵IDのリスト
		for (int id : enemyIDs) {
			auto ch = CharacterFactory::GetInstance().CreateCracter(SLIME);
			CharacterPoolManager::GetInstance().Release(SLIME, ch);
			
		}
	}

	const std::vector<std::shared_ptr<Character>>& GetPlayers() const {
		return players;
	}

	void ResetPlayerStatus() {
		for (auto& player : players) {
			if (player) {
				int id = player->GetID();
				const CharacterData* baseData = CharacterFactory::GetInstance().GetCharacterData(player->GetID());
				if (baseData) {
					player->ResetFromData(*baseData);
				}
			}
		}
	}

	std::shared_ptr<Character> AcquireEnemy(int id) {
		return CharacterPoolManager::GetInstance().Acquire(id);
	}

	void ReleaseEnemy(int id, std::shared_ptr<Character> enemy) {
		CharacterPoolManager::GetInstance().Release(id, enemy);
	}


	// 更新処理
	void Update();

	// スクリーン変更
	template<typename T>
	void ChangeScreen();

	// ステージ番号取得とセット
	int GetStageNumber() const { return stageNumber; }
	void SetStageNumber(int number) { stageNumber = number; }

};

template<typename T>
inline void ScreenManager::ChangeScreen()
{
	// スクリーンを変更
	currentScreen = std::make_shared<T>();
}
