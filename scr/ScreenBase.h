#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "view.h"
#include "Enum.h"
#include "Define.h"

// スクリーンの基底クラス
class ScreenBase {

protected:

public:

	// コンストラクタ
	ScreenBase() = default;
	// デストラクタ
	virtual ~ScreenBase() = default;

	// 更新処理
	virtual void Update() = 0;
};