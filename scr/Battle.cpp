#include "Battle.h"
#include "ScreenManager.h"
#include "Result.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

BattleScreen::BattleScreen()
{
    battle_view = std::make_shared<view>();
    state = State::Idle;
    baseEnemies = 2;
    currentPhase = 1;
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
        battle_view->ErrPlayer();
        state = State::Result;
        return;
    }

    // HP全回復
    for (auto& p : player) p->Heal();

    // エネミー生成
    enemyCount = baseEnemies + (currentPhase - 1);
    ScreenManager::GetInstance().SpawnSlimes(enemyCount);
    for (auto& e : ScreenManager::GetInstance().GetActiveEnemies()) {
        const CharacterData* pData = CharacterFactory::GetInstance().GetCharacterData(SLIME);
        if (pData) {
            e->SetData(*pData);
        }
    }
    
    battle_view->ShowPhase(currentPhase);
    state = State::Idle;
}

// ステート更新
void BattleScreen::Update() {
    switch (state) {

    case State::Idle:

        battle_view->ShowScreen();

        battle_view->StateMsg();

        for (auto& p : ScreenManager::GetInstance().GetPlayers()) {
            battle_view->PlayerState(p->GetName(), p->GetLv(), p->GetHP(), p->GetAttack(), p->GetDefense());
        }
        for (auto& e : ScreenManager::GetInstance().GetActiveEnemies()) {
            battle_view->EnemyState(e->GetName(), e->GetLv(), e->GetHP(), e->GetAttack(), e->GetDefense());
        }

        battle_view->StartBattle();

        state = State::PlayerTurn;

        break;
    
    case State::PlayerTurn:
        battle_view->PlayerTurnMsg();
        PlayerTurn();
        state = State::EnemyTurn;
        break;

    case State::EnemyTurn:
        battle_view->EnemyTurnMsg();
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
    battle_view->ChoiceAnnounce();
    std::cin >> action;

    battle_view->ChoiceMsg(action);

    if (action == 1) {

        auto& enemies = ScreenManager::GetInstance().GetActiveEnemies();

        for (auto& p : player) {
            // 生きてる敵を探す
            auto it = std::find_if(enemies.begin(), enemies.end(),
                [](auto& e) { return e->IsAlive(); });

            if (it == enemies.end()) break;

            auto enemy = *it;
            int dmg = std::max(1, p->GetAttack() - enemy->GetDefense());
            enemy->TakeDamage(dmg);

            battle_view->ShowDamage(p->GetName(), enemy->GetName(), dmg);
            battle_view->ShowHp(enemy->GetName(), enemy->GetHP());
            if (!enemy->IsAlive()) {
                battle_view->DestroySmg(enemy->GetName());
                p->LvUp();
            }
        }
    }
    else if (action == 2) {
        for (auto& p : player) {
            if (p->IsAlive()) {
                p->Heal();

                battle_view->ShowHeal(p->GetName(), p->GetHP(), p->GetMaxHP());

                battle_view->ShowHp(p->GetName(), p->GetHP());
            }
        }
    }
    else {
        battle_view->ErrSmg();
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

            battle_view->ShowDamage(e->GetName(), p->GetName(), dmg);
            battle_view->ShowHp(p->GetName(), p->GetHP());

            if (!p->IsAlive()) {
                battle_view->DestroySmg(p->GetName());
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
        battle_view->WinSmg();
        ScreenManager::GetInstance().EndBattle();
        return true;
    }
    if (allPlayersDead) {
        judg = Judg::Defeat;
        battle_view->OverSmg();
        return true;
    }
    return false;
}

// フェード切り替え
void BattleScreen::FadeTransition() {

    if (judg == Judg::Victory) {
        int choice;
        battle_view->QuestionPhase();
        std::cin >> choice;

        if (choice == 1) {
            battle_view->viewClr();
            currentPhase++;
            BattleStart();
        }
        else {
            battle_view->viewClr();
            ScreenManager::GetInstance().SetFadeNum(currentPhase);
            ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
        }
    }
    else if (judg == Judg::Defeat) {
        battle_view->viewClr();
        ScreenManager::GetInstance().SetFadeNum(currentPhase);
        ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
    }
}
