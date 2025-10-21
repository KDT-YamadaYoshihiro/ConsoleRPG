#include "Result.h"
#include "ScreenManager.h"
#include <iostream>

ResultScreen::ResultScreen()
{
}

void ResultScreen::SetPlayer(std::vector<std::shared_ptr<Character>> p) {
    player = p;
}

void ResultScreen::SetLastFade(int fade) {
    lastFade = fade;
}

void ResultScreen::Update() {

    SetLastFade(ScreenManager::GetInstance().GetFadeNum());

    if (!displayed) {
        player = ScreenManager::GetInstance().GetPlayers();

        for (auto& p : player) {
            if (!p) {
                std::cerr << "[Error] リザルトスクリーンにてプレイヤーが見つかりませんでした\n";
                return;
            }

            std::cout << "\n=== Result Screen ===\n";
            std::cout << "Last Fade: " << lastFade << "\n";
            std::cout << "Player: " << p->GetName() << "\n";
            std::cout << "LV: " << p->GetData().Lv
                << " HP: " << p->GetHP() << "/" << p->GetMaxHP()
                << " ATK: " << p->GetAttack()
                << " DEF: " << p->GetDefense() << "\n";

            std::cout << "\n1: Retry  2: Exit\n";
            displayed = true;
        }
    }

    int choice = 0;
    std::cin >> choice;

    if (choice == 1) {
        // 再挑戦の場合、プレイヤーのステータスを初期化
        if (ScreenManager::GetInstance) {
            ScreenManager::GetInstance().ResetPlayerStatus();
        }
        std::cout << "Restarting battle...\n";
        // 画面を遷移
        system("cls");
        ScreenManager::GetInstance().ChangeScreen<BattleScreen>();
    }
    else if (choice == 2) {
        system("cls");
        std::cout << "Exiting game...\n";
        return;
    }
}
