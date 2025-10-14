#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// スクリーンの基底クラス
class ScreenBase {
public:

	// コンストラクタ
	ScreenBase() = default;
	// デストラクタ
	virtual ~ScreenBase() = default;

	// 更新処理
	virtual void Update() = 0;
};