#include "Battle.h"
#include "ScreenManager.h"

Battle::Battle()
{
	// 初期化
	// ステージ番号を取得
	int stageNumber = ScreenManager::GetInstance().GetStageNumber();
	// ステージ番号に応じたエネミーを生成
	GenerateEnemy(stageNumber);
}

void Battle::Update()
{
	// 戦闘処理
	switch (battleMode)
	{
	case BATTLE_MODE::PLAYER_TURN:

		PlayerAction();

		battleMode = BATTLE_MODE::ENEMY_TURN;

		break;
	case BATTLE_MODE::ENEMY_TURN:

		EnemyAction();

		battleMode = BATTLE_MODE::PLAYER_TURN;

		break;
	case BATTLE_MODE::BATTLE_OVER:

		// 戦闘終了処理
		CheckVictory();

		break;

	default:
		break;
	}
	// 
}

void Battle::Draw() const
{
}

void Battle::GenerateEnemy(int arg_stageNumber)
{
	std::shared_ptr<Character> enemy;
	// ステージ番号に応じたエネミーを生成
	switch (arg_stageNumber)
	{
	case 1:

		enemy = CharacterFactory::GetInstance().CreateCracter(SLIME);
		enemis.push_back(enemy);

		break;
	case 2:
		enemy = CharacterFactory::GetInstance().CreateCracter(GOBLIN);
		enemis.push_back(enemy);
		break;

	case 3:
		enemy = CharacterFactory::GetInstance().CreateCracter(WOLF);
		enemis.push_back(enemy);
		break;


	default:
		// デフォルトのエネミーを生成
		enemy = CharacterFactory::GetInstance().CreateCracter(SLIME);
		enemis.push_back(enemy);

		break;
	}
}

bool Battle::CheckVictory()
{
	// バトルの勝敗、続行を判定
	// return 決着 : 続行 ? true ：false
	// 決着した場合はisBattleOverにセット（勝利:true、敗北:false）

	// プレイヤーの生存判定を行う
	for (const auto& player : players) {
		if (player->GetHP() <= 0) {
			isBattleOver = false;
			return true;
		}
	}

	// エネミーの生存判定を行う
	for (const auto& enemy : enemis) {
		if (enemy->GetHP() <= 0) {
			isBattleOver = true;
			return true;
		}
	}


	return false;
}

void Battle::PlayerAction()
{

	// プレイヤーの行動選択
	// 行動するプレイヤーを選択
	std::cout << "行動するプレイヤーを選択してください\n";
	std::cout << "1~4の中から入力してください\n";

	int playerIndex = -1;
	std::cin >> playerIndex;

	// 入力の妥当性を確認
	while (playerIndex < 1 || playerIndex > 4) {
		std::cout << "無効な選択です。もう一度入力してください。\n";
		std::cin >> playerIndex;
	}

	// 選択されたプレイヤーの行動を実行
	players[playerIndex]->ChooseAction(enemis[0]);


}

void Battle::EnemyAction()
{
	// エネミーの行動
}
