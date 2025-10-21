#include "Battle.h"
#include "ScreenManager.h"
#include "Result.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

BattleScreen::BattleScreen()
{
    state = State::Idle;
    baseEnemies = 2;
    currentFade = 1;
    DeadEnemies = 0;
    BattleStart();
}

// プレイヤーセット
void BattleScreen::SetPlayer(std::vector<std::shared_ptr<Character>> p) {
    player = p;
}

// バトル開始（敵生成・プレイヤー回復）
void BattleScreen::BattleStart() {
    DeadEnemies = 0;

    player = ScreenManager::GetInstance().GetPlayers();
    if (player.empty()) {
        std::cerr << "[Error] プレイヤーが存在しません!\n";
        state = State::Result;
        return;
    }

    // HP全回復
    for (auto& p : player) p->Heal();

    // エネミー生成
    enemyCount = baseEnemies + (currentFade - 1);
    ScreenManager::GetInstance().SpawnSlimes(enemyCount);
    for (auto& e : ScreenManager::GetInstance().GetActiveEnemies()) {
        const CharacterData* pData = CharacterFactory::GetInstance().GetCharacterData(SLIME);
        if (pData) {
            e->SetData(*pData);
        }
    }

    std::cout << "\n=== フェーズ " << currentFade << " 開始 ===\n";
    state = State::Idle;
}

// ステート更新
void BattleScreen::Update() {
    switch (state) {

    case State::Idle:

        std::cout << "---【バトル開始】---" << std::endl;

        for (auto& p : ScreenManager::GetInstance().GetPlayers()) {
            std::cout << "プレイヤー\n" << "name:" << p->GetName() << "\nLv:" << p->GetLv() << " HP:" << p->GetHP() << std::endl;
        }
        for (auto& e : ScreenManager::GetInstance().GetActiveEnemies()) {
            std::cout << "エネミー\n" << "name:" << e->GetName() << "\nLv:" << e->GetLv() << " HP:" << e->GetHP() << std::endl;
        }

        state = State::PlayerTurn;

        break;
    
    case State::PlayerTurn:
        std::cout << "\n--- プレイヤーのターン ---\n";
        PlayerTurn();
        state = State::EnemyTurn;
        break;

    case State::EnemyTurn:
        std::cout << "\n--- エネミーのターン ---\n";
        EnemyTurn();
        state = State::CheckResult;
        break;

    case State::CheckResult:
        if (Victoryjudg()) {
            state = State::FadeTransition;
        }
        else {
            state = State::PlayerTurn;
        }
        break;

    case State::FadeTransition:
        FadeTransition();
        break;

    default:
        break;
    }
}

// プレイヤー行動
void BattleScreen::PlayerTurn() {
    int action = 0;
    std::cout << "行動を選択：1=攻撃 2=回復 >> ";
    std::cin >> action;

    if (action == 1) {
        std::cout << "\n攻撃が選択されました。\n";
        auto& enemies = ScreenManager::GetInstance().GetActiveEnemies();

        for (auto& p : player) {
            // 生きてる敵を探す
            auto it = std::find_if(enemies.begin(), enemies.end(),
                [](auto& e) { return e->IsAlive(); });

            if (it == enemies.end()) break;

            auto enemy = *it;
            int dmg = std::max(1, p->GetAttack() - enemy->GetDefense());
            enemy->TakeDamage(dmg);

            std::cout << p->GetName() << " は " << enemy->GetName()
                << " に " << dmg << " のダメージ！\n";

            std::cout << enemy->GetName() << "の残りHPは" << enemy->GetHP() << std::endl;;

            if (!enemy->IsAlive()) {
                std::cout << enemy->GetName() << " を倒した！\n";
                p->LvUp();
            }
        }
    }
    else if (action == 2) {
        std::cout << "\n回復が選択されました。\n";
        for (auto& p : player) {
            if (p->IsAlive()) {
                p->Heal();
                std::cout << p->GetName() << " は回復した！ HP:"
                    << p->GetHP() << "/" << p->GetMaxHP() << "\n";

                std::cout << p->GetName() << "の残りHPは" << p->GetHP() << std::endl;
            }
        }
    }
    else {
        std::cout << "無効な入力です。\n";
        std::cin >> action;
    }
}

// エネミー行動
void BattleScreen::EnemyTurn() {
    auto& enemies = ScreenManager::GetInstance().GetActiveEnemies();
    for (auto& e : enemies) {
        if (!e->IsAlive()) continue;

        for (auto& p : player) {
            if (!p->IsAlive()) continue;

            int dmg = std::max(1, e->GetAttack() - p->GetDefense());
            p->TakeDamage(dmg);

            std::cout << e->GetName() << " は " << p->GetName()
                << " に " << dmg << " のダメージ！\n";

            std::cout << p->GetName() << "の残りHPは" << p->GetHP() << std::endl;

            if (!p->IsAlive()) {
                std::cout << p->GetName() << " は倒れた！\n";
            }
            break; // 1ターン1回攻撃
        }
    }
}

// 勝敗判定
bool BattleScreen::Victoryjudg() {
    bool allEnemiesDead = true;
    for (auto& e : ScreenManager::GetInstance().GetActiveEnemies()) {
        if (e->IsAlive()) allEnemiesDead = false;
    }

    bool allPlayersDead = true;
    for (auto& p : player) {
        if (p->IsAlive()) allPlayersDead = false;
    }

    if (allEnemiesDead) {
        judg = Judg::Victory;
        std::cout << "\n敵は全滅した！勝利！\n";
        ScreenManager::GetInstance().EndBattle();
        return true;
    }
    if (allPlayersDead) {
        judg = Judg::Defeat;
        std::cout << "\n全滅した...敗北。\n";
        return true;
    }
    return false;
}

// フェード切り替え
void BattleScreen::FadeTransition() {

    if (judg == Judg::Victory) {
        std::cout << "\n次のフェーズに進みますか？(1:はい 2:いいえ) >> ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            system("cls");
            currentFade++;
            BattleStart();
        }
        else {
            system("cls");
            ScreenManager::GetInstance().SetFadeNum(currentFade);
            ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
            std::cout << "バトル終了。\n";

        }
    }
    else if (judg == Judg::Defeat) {
        system("cls");
        std::cout << "バトル終了。\n";
        ScreenManager::GetInstance().SetFadeNum(currentFade);
        ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
    }
}
