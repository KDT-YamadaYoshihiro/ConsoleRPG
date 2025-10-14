#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "ScreenBase.h"
#include "Character.h"
#include "CharacterFactory.h"
#include "Title.h"

class ScreenManager {

	// ステージ番号
	int stageNumber = 0;

	// プレイヤー
	std::vector<std::shared_ptr<Character>> players;


	std::shared_ptr<ScreenBase> currentScreen = nullptr;

	// コンストラクタ
	//　初期化
	ScreenManager() {

		// 最初のスクリーンはタイトル
		if (currentScreen == nullptr) {
			currentScreen = std::make_shared<Title>();
		}
		for (int i = 0; i < 4; i++){
			players.push_back(CharacterFactory::GetInstance().CreateCracter(i));
		}
	};
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

	// 更新処理
	void Update();

	// スクリーン変更
	template<typename T>
	void ChangeScreen(std::shared_ptr<T> newScreen);

	// ステージ番号取得とセット
	int GetStageNumber() const { return stageNumber; }
	void SetStageNumber(int number) { stageNumber = number; }

	// プレイヤー取得
	const std::vector<std::shared_ptr<Character>>& GetPlayers() const { return players; }

};

template<typename T>
inline void ScreenManager::ChangeScreen(std::shared_ptr<T> newScreen)
{
	// スクリーンを変更
	currentScreen = newScreen;
}
