#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "ScreenBase.h"
#include "Battle.h"

#include "Character.h"
#include "Enemy.h"
#include "CharacterFactory.h"
#include "ObjectPool.h"


class ScreenManager {

	// ステージ番号
	int stageNumber = 0;

	// ビュークラス
	std::shared_ptr<view> manager_view;

	// プレイヤーキャラクター
	std::vector<std::shared_ptr<Character>> players;
	// スライム用プール
	ObjectPool<Enemy> slimePool;
	// 現在バトル中のエネミー
	std::vector<std::shared_ptr<Enemy>> activeEnemies;

	std::shared_ptr<ScreenBase> currentScreen = nullptr;

	// 最終フェード数（リザルトで使用）
	int fadeNum = 0;

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
		if (!akira) {
			std::cout << "アキラの生成に失敗しました" << std::endl;
		}
		players.push_back(akira);
	}

	// プレイヤー取得
	const std::vector<std::shared_ptr<Character>>& GetPlayers() const {
		return players;
	}

	// プレイヤーステータスリセット
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

	// スライム生成
	void SpawnSlimes(int count) {
		activeEnemies.clear();

		for (int i = 0; i < count; ++i) {
			// プールからスライム取得
			auto handle = slimePool.Acquire();
			auto slime = handle.Detach();

			// スライムのデータ初期化
			const auto* data = CharacterFactory::GetInstance().GetCharacterData(SLIME);
			if (data) {
				*slime = Enemy(*data);
			}

			activeEnemies.push_back(slime);
		}
	}

	// アクティブなエネミー取得
	const std::vector<std::shared_ptr<Enemy>>& GetActiveEnemies() const {
		return activeEnemies;
	}

	// アクティブなエネミー取得（非const版）
	void EndBattle() {
		// バトル終了時、全エネミーをプールに返却
		for (auto& e : activeEnemies) {
			slimePool.Release(e);
		}
		activeEnemies.clear();
	}

	// 更新処理
	void Update();

	// スクリーン変更
	template<typename T>
	void ChangeScreen();

	// ステージ番号取得とセット
	int GetStageNumber() const { return stageNumber; }
	void SetStageNumber(int number) { stageNumber = number; }

	// フェード数のセットと取得
	int GetFadeNum() const { return fadeNum; }
	void SetFadeNum(int arg_fadeNum) { fadeNum = arg_fadeNum; }

};

template<typename T>
inline void ScreenManager::ChangeScreen()
{
	// スクリーンを変更
	currentScreen = std::make_shared<T>();
}
