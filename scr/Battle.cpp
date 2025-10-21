#include "Battle.h"
#include "ScreenManager.h"
#include "Result.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

// コンストラクタ（引数なし）
BattleScreen::BattleScreen()
    : enemyPool(10)  // ObjectPool を初期化
{
    state = State::Idle;
    baseEnemies = 2;   // 初期敵数
    currentFade = 1;
    BattleStart();
}

// プレイヤーセット
void BattleScreen::SetPlayer(std::vector<std::shared_ptr<Character>> p) {
    player = p;
}

// バトル開始（敵生成・プレイヤー回復）
void BattleScreen::BattleStart() {

    player = ScreenManager::GetInstance().GetPlayers();
    for (auto& p : player) {
        if (!p) {
            std::cerr << "[Error] プレイヤーが存在しません!\n";
            state = State::Result;
            return;
        }
    }
    for (auto& p : player) {
        p->Heal();  // HP回復
    }

    // リストをリセット
    enemies.clear();

    int enemyCount = 2 + (currentFade - 1); 
    for (int i = 0; i < enemyCount; ++i) {
        int id = SLIME;
        auto enemy = ScreenManager::GetInstance().AcquireEnemy(id);
        if (enemy) {
            enemies.push_back(enemy);
        }
    }

    if (enemies.empty()) {
        std::cerr << "[Error] 敵が発生しません!\n";
        state = State::Result;
        return;
    }

    state = State::Idle;
    std::cout << "--- Battle Fade " << currentFade << " Start ---\n";
}

// Update（スイッチ文によるステート管理）
void BattleScreen::Update() {



    switch (state) {
    case State::Idle:
        for (auto& p : player) {
            std::cout << "\n--- バトル開始 ---\n";
            std::cout << "プレイヤー: " << p->GetName()
                << " HP:" << p->GetHP() << "/" << p->GetMaxHP() << "\n";
            std::cout << "敵の数: " << enemies.size() << "\n";
            for (auto& e : enemies) {
                std::cout << "エネミーHP：" << e->GetHP() << std::endl;
            }
            state = State::PlayerTurn;
        }
        break;

    case State::PlayerTurn:
        std::cout << "\n--- プレイヤーのターン ---\n";
        PlayerTurn();

        for (auto& e : enemies) {

            if (e->IsAlive()) {
                DeadEnemies++;
            }
        }

        if (DeadEnemies == enemies.size()) {
            state = State::CheckResult;
        }
        else {
            state = State::EnemyTurn;
        }


        break;

    case State::EnemyTurn:
        std::cout << "\n--- エネミーのターン ---\n";
        
        EnemyTurn();

        for (auto& p : player) {
            if (p->IsAlive()) {
                state = State::CheckResult;
            }
            else {
                state = State::PlayerTurn;
            }
        }
        break;

    case State::CheckResult:

        for(auto& p : player){
            if (p->IsAlive()) {
                std::cout << "プレイヤーが敗北しました！戦闘終了\n";
                ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
                state = State::Idle;
            }
            return;
        }

        for (auto& e : enemies) {

            if (e->IsAlive()) {
                DeadEnemies++;
            }
        }

        if (DeadEnemies == enemies.size()) {
            std::cout << "全ての敵を倒しました！\n";
            state = State::FadeTransition;
        }


        break;

    case State::FadeTransition: {
        std::cout << "次のフェードに進みますか?\n1: はい  2: いいえ\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            currentFade++;
            BattleStart(); // 敵再生成・HP回復
            state = State::Idle;
        }
        else if (choice == 2) {
            std::cout << "バトル終了\n";
            ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
            state = State::Idle;
        }
        else {
            std::cout << "無効な入力です。再度選択してください。\n";
        }
        break;
    }

    default:
        break;
    }
}

// プレイヤー行動
void BattleScreen::PlayerTurn() {

    std::cout << "行動を選択して下しださい\n攻撃：１　回復：２" << std::endl;
    int action;
    std::cin >> action;

    if (action == 1) {

        std::cout << "攻撃が選択されました。" << std::endl;
        for (auto& enemy : enemies) {

            for (auto& p : player) {
                if (enemy->IsAlive()) {
                    int dmg = std::max(1, p->GetAttack() - enemy->GetDefense());
                    enemy->TakeDamage(dmg);

                    std::cout << p->GetName().c_str() << " は " << enemy->GetName().c_str()
                        << " に " << dmg << " のダメージを与えた\n";

                    if (!enemy->IsAlive()) {
                        p->LvUp();
                        std::cout << enemy->GetName().c_str() << " を倒した！ プレイヤーLV:"
                            << p->GetData().Lv << "\n";
                        enemyPool.Release(enemy);
                    }
                    break; // 1ターンにつき1体攻撃
                }
            }
        }

    }
    else if (action == 2) {

        std::cout << "回復が選択されました" << std::endl;
        for (auto& p : player) {
            if (p->IsAlive()) {
                
                p->Heal();
                int heal = p->GetMaxHP() * 0.6;

                std::cout << p->GetName().c_str() << "は" << heal << "回復した！\n" << "HP:" << p->GetHP();
            }
            break;
        }
    }
    else {
        std::cout << "無効な数値が入力されました。もう一度入力してください" << std::endl;
        std::cin >> action;
    }


}

// エネミー行動
void BattleScreen::EnemyTurn() {
    for (auto& enemy : enemies) {
        for (auto& p : player) {
            if (enemy->IsAlive()) {
                int dmg = std::max(1, enemy->GetAttack() - p->GetDefense());
                p->TakeDamage(dmg);

                std::cout << enemy->GetName() << " は " << p->GetName()
                    << " に " << dmg << " のダメージを与えた\n";
            }
        }
    }
}

// 全敵死亡判定
bool BattleScreen::AllEnemiesDead() const {
    return std::all_of(enemies.begin(), enemies.end(), [](const std::shared_ptr<Character>& e) {
        return !e->IsAlive();
        });
}

// フェード数に応じた敵選択
int BattleScreen::ChooseEnemyID() const {
    int ids[] = { SLIME, GOBLIN, WOLF };
    return ids[rand() % 4];
}
