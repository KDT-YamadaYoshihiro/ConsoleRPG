#include "Battle.h"
#include "ScreenManager.h"
#include "Result.h"
#include "Enum.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

// コンストラクタ
// 初期化
BattleScreen::BattleScreen()
{
    battle_view = std::make_shared<view>();
	calc = std::make_shared<Calculation>();
    state = State::Idle;
    baseEnemies = START_ENEMY;
    currentPhase = START_PHASE;
    DeadEnemies = START_DEADENEMY;
    BattleStart();
}

// バトル開始（敵生成・プレイヤー回復）
void BattleScreen::BattleStart() {
	// 死亡した敵数リセット
    DeadEnemies = START_DEADENEMY;
	// プレイヤー取得
    player = ScreenManager::GetInstance().GetPlayers();
	// プレイヤーがいない場合エラー
    if (player.empty()) {
        battle_view->ErrPlayer();
        state = State::Result;
        return;
    }

    // HP全回復
    for (auto& p : player) p->Heal();

    // エネミー生成
    enemyCount = baseEnemies + (currentPhase);
    ScreenManager::GetInstance().SpawnSlimes(enemyCount);
    for (auto& e : ScreenManager::GetInstance().GetActiveEnemies()) {
        const CharacterData* pData = CharacterFactory::GetInstance().GetCharacterData(SLIME);
        if (pData) {
            e->SetData(*pData);
        }
    }
	// フェーズ表示
    battle_view->ShowPhase(currentPhase);
    state = State::Idle;
}

// ステート更新
void BattleScreen::Update() {

	// ステートマシン
    switch (state) {

	case State::Idle:               // バトル開始前、案内表示用

		// スクリーン表示
        battle_view->ShowScreen();

		//　ステータス表示
        battle_view->StateMsg();

		// プレイヤーステータス
        for (auto& p : ScreenManager::GetInstance().GetPlayers()) {
            battle_view->PlayerState(p->GetName(), p->GetLv(), p->GetHP(), p->GetAttack(), p->GetDefense());
        }
		// エネミーステータス
        for (auto& e : ScreenManager::GetInstance().GetActiveEnemies()) {
            battle_view->EnemyState(e->GetName(), e->GetLv(), e->GetHP(), e->GetAttack(), e->GetDefense());
        }

		// バトル開始メッセ
        battle_view->StartBattle();
        // プレイヤーターンへ
        state = State::PlayerTurn;

        break;
    
	case State::PlayerTurn:         // プレイヤー行動フェーズ

        // メッセージの表示
        battle_view->PlayerTurnMsg();
        // プレイヤーの行動
        PlayerTurn();
		// エネミーターンへ
        state = State::EnemyTurn;

        break;

	case State::EnemyTurn:		  // エネミー行動フェーズ 
		// メッセージの表示
        battle_view->EnemyTurnMsg();
		// エネミーの行動
        EnemyTurn();
		// 勝敗判定へ
        state = State::CheckResult;

        break;

	case State::CheckResult:	  // 勝敗判定

        // 勝敗判定
        if (Victoryjudg()) {
			// フェード進行へ
            state = State::FadeTransition;
        }
        else {
			// プレイヤーターンへ
            state = State::PlayerTurn;
        }
        break;

	case State::FadeTransition:	  // フェード進行確認フェーズ
		// フェード進行
        FadeTransition();
        break;

    default:
        break;
    }
}

// プレイヤー行動
void BattleScreen::PlayerTurn() {

	// 行動選択
    int action = 0;
	// アクション選択案内
    battle_view->ChoiceAnnounce();
	// 入力受付
    std::cin >> action;

	// 選択結果表示
    battle_view->ChoiceMsg(action);

	// 行動処理
    if (action == ACTION::ATTACK) {

		// 生成されている敵を取得
        auto& enemies = ScreenManager::GetInstance().GetActiveEnemies();

        for (auto& p : player) {
            // 生きてる敵を探す
            auto it = std::find_if(enemies.begin(), enemies.end(),
                [](auto& e) { return e->IsAlive(); });

			// 敵がいなければ終了
            if (it == enemies.end())
            {
                break;
            }

			// 攻撃処理
			auto e = *it;
            // ダメージ計算
            int dmg = calc->DamageCalc(p->GetAttack(), e->GetDefense());
            // エネミーにダメージを与える
            e->TakeDamage(dmg);

            // ダメージ表示
            battle_view->ShowDamage(p->GetName(), e->GetName(), dmg);
            // エネミーのHP表示
            battle_view->ShowHp(e->GetName(), e->GetHP());

            // 敵が倒れた場合の処理
            if (!e->IsAlive()) {
                battle_view->DestroySmg(e->GetName());
                p->LvUp();
            }
            
        }
    }
    else if (action == ACTION::HEAL) {

		// 回復処理
        for (auto& p : player) {
			// 生きている場合回復
            if (p->IsAlive()) {
				// 回復
                p->Heal();

				// 回復表示
                battle_view->ShowHeal(p->GetName(), p->GetHP(), p->GetMaxHP());
				// HP表示
                battle_view->ShowHp(p->GetName(), p->GetHP());
            }
        }
    }
    else {
		// エラーの入力値
        battle_view->ErrSmg();
        std::cin >> action;
    }
}

// エネミー行動
void BattleScreen::EnemyTurn() {
	// 生成されている敵を取得
    auto& enemies = ScreenManager::GetInstance().GetActiveEnemies();

	// エネミーの行動処理
    for (auto& e : enemies) {
		// 生きているエネミーのみ処理
        if (!e->IsAlive())
        {
            continue;
        }

		// プレイヤーを攻撃
        for (auto& p : player) {

			// 生きているプレイヤーのみ攻撃
            if (!p->IsAlive())
            {
                continue;
            }

			//　ダメージ計算
            int dmg = calc->DamageCalc(e->GetAttack(), p->GetDefense());
			// プレイヤーにダメージを与える
            p->TakeDamage(dmg);

            // ダメージ表示
            battle_view->ShowDamage(e->GetName(), p->GetName(), dmg);
			// プレイヤーのHP表示
            battle_view->ShowHp(p->GetName(), p->GetHP());

			// プレイヤーが倒れた場合の処理
            if (!p->IsAlive()) {
                battle_view->DestroySmg(p->GetName());
            }
            break; // 1ターン1回攻撃
        }
    }
}

// 勝敗判定
bool BattleScreen::Victoryjudg() {

	// 全エネミーが倒れたか判定
    bool allEnemiesDead = true;
    for (auto& e : ScreenManager::GetInstance().GetActiveEnemies()) {
        if (e->IsAlive()) allEnemiesDead = false;
    }

	// 全プレイヤーが倒れたか判定
    bool allPlayersDead = true;
    for (auto& p : player) {
        if (p->IsAlive()) allPlayersDead = false;
    }

	// 勝敗処理
    if (allEnemiesDead) {
        // 勝利判定
        judg = Judg::Victory;
        // 勝利メッセ
        battle_view->WinSmg();
		// バトル終了処理
        ScreenManager::GetInstance().EndBattle();
        return true;
    }
    if (allPlayersDead) {
		// 敗北判定
        judg = Judg::Defeat;
		// 敗北メッセ
        battle_view->OverSmg();
        return true;
    }
    return false;
}

// フェード切り替え
void BattleScreen::FadeTransition() {

	// 勝利時の選択肢
    if (judg == Judg::Victory) {

        // バトルの続行確認
        int choice;
        battle_view->QuestionPhase();
        std::cin >> choice;

        if (choice == NEXT_PHASE) {
			// 次のフェーズへ
            battle_view->viewClr();
			// フェーズ進行
            currentPhase++;
			// バトル再開（初期化）
            BattleStart();
        }
        else if(choice == TO_RESULT){
            // 画面をクリア
            battle_view->viewClr();
			// 勝利したフェード数をセット
            ScreenManager::GetInstance().SetFadeNum(currentPhase);
            // リザルト画面へ
            ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
        }
        else {
            // エラーの入力値
			battle_view->ErrSmg();
			std::cin >> choice;
        }
    }
    else if (judg == Judg::Defeat) {

		// 画面をクリア
        battle_view->viewClr();
		// 勝利したフェード数をセット
        ScreenManager::GetInstance().SetFadeNum(currentPhase);
		// リザルト画面へ
        ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
    }
}
