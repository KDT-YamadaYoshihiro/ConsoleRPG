#include "Battle.h"
#include "ScreenManager.h"
#include "Result.h"

// コンストラクタ
// 初期化
BattleScreen::BattleScreen()
{
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
        view::Instance().ErrPlayer();
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
    view::Instance().ShowPhase(currentPhase);
    state = State::Idle;
}

// ステート更新
void BattleScreen::Update() {

	// ステートマシン
    switch (state) {

	case State::Idle:               // バトル開始前、案内表示用

		// スクリーン表示
        view::Instance().ShowScreen();
		//　ステータス表示
        view::Instance().StateMsg();
		// プレイヤーステータス
        for (auto& p : ScreenManager::GetInstance().GetPlayers()) {
           view::Instance().DispCharaStatus(p->GetType(), p->GetData());
        }
		// エネミーステータス
        for (auto& e : ScreenManager::GetInstance().GetActiveEnemies()) {
            view::Instance().DispCharaStatus(e->GetType(), e->GetData());
        }
		// バトル開始メッセ
        view::Instance().StartBattle();
        // プレイヤーターンへ
        state = State::PlayerTurn;

        break;
    
	case State::PlayerTurn:         // プレイヤー行動フェーズ

        // メッセージの表示
        view::Instance().PlayerTurnMsg();
        // プレイヤーの行動
        PlayerTurn();
		// エネミーターンへ
        state = State::EnemyTurn;

        break;

	case State::EnemyTurn:		  // エネミー行動フェーズ 

		// メッセージの表示
        view::Instance().EnemyTurnMsg();
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
    }
}

// プレイヤー行動
void BattleScreen::PlayerTurn() {
	// プレイヤーの選択肢取得
    int action = GetPlayerAction();  // プレイヤーの選択を取得

    // 行動処理
    switch (action) {
        case ACTION::ATTACK:
            PlayerAttack();
            break;
        case ACTION::HEAL:
            PlayerHeal();
            break;
        default:
            view::Instance().ErrSmg();
            break;
    }
}
// プレイヤーの選択肢取得
int BattleScreen::GetPlayerAction() {
    int action = 0;
    view::Instance().ChoiceAnnounce();
    std::cin >> action;
    return action;
}
// プレイヤー攻撃
void BattleScreen::PlayerAttack() {
    auto& enemies = ScreenManager::GetInstance().GetActiveEnemies();
    for (auto& p : player) {
        auto it = std::find_if(enemies.begin(), enemies.end(), [](auto& e) { return e->IsAlive(); });
        if (it == enemies.end()) break;
        
        auto e = *it;
        int dmg = Calculation::DamageCalc(p->GetAttack(), e->GetDefense());
        e->TakeDamage(dmg);
        view::Instance().ShowDamage(p->GetName(), e->GetName(), dmg);
        view::Instance().ShowHp(e->GetName(), e->GetHP());

        if (!e->IsAlive()) {
            view::Instance().DestroySmg(e->GetName());
            p->LvUp();
        }
    }
}
// プレイヤー回復
void BattleScreen::PlayerHeal() {
    for (auto& p : player) {
        if (p->IsAlive()) {
            p->Heal();
            view::Instance().ShowHeal(p->GetName(), p->GetHP(), p->GetMaxHP());
            view::Instance().ShowHp(p->GetName(), p->GetHP());
        }
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
            int dmg = Calculation::DamageCalc(e->GetAttack(), p->GetDefense());
			// プレイヤーにダメージを与える
            p->TakeDamage(dmg);

            // ダメージ表示
            view::Instance().ShowDamage(e->GetName(), p->GetName(), dmg);

			// プレイヤーのHP表示
            view::Instance().ShowHp(p->GetName(), p->GetHP());

			// プレイヤーが倒れた場合の処理
            if (!p->IsAlive()) {
                view::Instance().DestroySmg(p->GetName());
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
        view::Instance().WinSmg();
		// バトル終了処理
        ScreenManager::GetInstance().EndBattle();
        return true;
    }
    if (allPlayersDead) {
		// 敗北判定
        judg = Judg::Defeat;
		// 敗北メッセ
        view::Instance().OverSmg();
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
        view::Instance().QuestionPhase();
        std::cin >> choice;

        if (choice == NEXT_PHASE) {
			// 次のフェーズへ
            view::Instance().viewClr();
			// フェーズ進行
            currentPhase++;
			// バトル再開（初期化）
            BattleStart();
        }
        else if(choice == TO_RESULT){
            // 画面をクリア
            view::Instance().viewClr();
			// 勝利したフェード数をセット
            ScreenManager::GetInstance().SetFadeNum(currentPhase);
            // リザルト画面へ
            ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
        }
        else {
            // エラーの入力値
            view::Instance().ErrSmg();
			std::cin >> choice;
        }
    }
    else if (judg == Judg::Defeat) {

		// 画面をクリア
        view::Instance().viewClr();
		// 勝利したフェード数をセット
        ScreenManager::GetInstance().SetFadeNum(currentPhase);
		// リザルト画面へ
        ScreenManager::GetInstance().ChangeScreen<ResultScreen>();
    }
}
