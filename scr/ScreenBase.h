#pragma once
#include <iostream>
#include <vector>

enum class SCREEN {
	TITLE,
	STAGE,
	BATTLE,
	RESULT,
};

class Screen {

	SCREEN screen;

public:

	// コンストラクタ
	//　初期化
	Screen()
		:screen(SCREEN::TITLE) 
	{
	};

	// 更新処理
	void Update();
	// 描画
	void Draw();
	

};