#pragma once
#include <iostream>

class ScreenBase {
public:

	// コンストラクタ
	ScreenBase() = default;
	// デストラクタ
	virtual ~ScreenBase() = default;

	// 更新処理
	virtual void Update() = 0;
	// 描画処理
	virtual void Draw() const = 0;
};