#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "view.h"

// スクリーンの基底クラス
class ScreenBase {

protected:

	// ビュークラス
	std::shared_ptr<view> screen_view;

public:

	// コンストラクタ
	ScreenBase() = default;
	// デストラクタ
	virtual ~ScreenBase() = default;

	// 更新処理
	virtual void Update() = 0;
};