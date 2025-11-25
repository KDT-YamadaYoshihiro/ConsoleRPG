#include "Result.h"
#include "ScreenManager.h"
#include "GameManager.hpp"

// コンストラクタ
// 初期化
ResultScreen::ResultScreen()
{
}

// 最終フェード数セット関数
void ResultScreen::SetLastFade(int fade) {
    lastFade = fade;
}

// 更新処理
void ResultScreen::Update() {

	// 最終フェード数を取得
    SetLastFade(ScreenManager::GetInstance().GetFadeNum());

	// リザルト表示
    // 
    if (!displayed) {
		// プレイヤー情報取得
        player = ScreenManager::GetInstance().GetPlayers();

		// プレイヤー情報表示
        for (auto& p : player) {
			// プレイヤーが見つからない場合エラー
            if (!p) {
				// エラー表示
                view::Instance().ErrPlayer();
                return;
            }

			// リザルト画面表示
            view::Instance().ResultScreen(lastFade, p);

			// 表示済みフラグを立てる
            displayed = true;
        }
    }

    int choice = 0;
	// 再挑戦 or 終了の案内
    std::cin >> choice;

    if (choice == RETRY) {
        // 再挑戦の場合、プレイヤーのステータスを初期化
        if (ScreenManager::GetInstance) {
            ScreenManager::GetInstance().ResetPlayerStatus();
        }

		// 再挑戦メッセ
        view::Instance().RetryMsg();
        // 画面を遷移
        view::Instance().viewClr();
        ScreenManager::GetInstance().ChangeScreen<BattleScreen>();
    }
    else if (choice == EXIT) {
        view::Instance().viewClr();
		// 終了メッセ
        view::Instance().ExitMsg();
        GameManager::Instace().Finalize();
        return;
    }
}
