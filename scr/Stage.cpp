#include "Stage.h"
#include "Battle.h"
#include "ScreenManager.h"

void Stage::Update()
{
	int stageNumber = -1;
	int trans = -1;

	switch (mode)
	{
	case MODE::SELECT:

		// ステージ選択を促す
		std::cout << "ステージを選択してください" << std::endl << "1~3の中から入力してください";
		std::cin >> stageNumber;

		mode = MODE::COF;

		break;

	case MODE::COF:

		if (stageNumber >= 1 && stageNumber <= 3) {
			std::cout << stageNumber << "ステージを選択しました" << std::endl;
			// 
			mode = MODE::TRANSITION;
		}
		else {
			std::cout << "無効なステージ番号です。1～3の範囲で選択してください。" << std::endl;
			mode = MODE::SELECT;
		}
		break;

	case MODE::TRANSITION:

			std::cout << stageNumber << "ステージに挑戦しますか？" << std::endl << "1:はい 2:いいえ" << std::endl;
			std::cin >> trans;
			if (trans == 1) {

				// ステージ番号を保存する
				ScreenManager::GetInstance().SetStageNumber(stageNumber);
				// 戦闘画面へ遷移
				ScreenManager::GetInstance().ChangeScreen(std::shared_ptr<Battle>());
				// スクリーンをクリアにする
				system("cls");

			}
			else if (trans == 2) {
				mode = MODE::SELECT;
				// スクリーンをクリアにする
				system("cls");

			}
			else {
				std::cout << "無効な選択です。1または2を入力してください。" << std::endl;
				mode = MODE::TRANSITION;
			}

		break;

	default:
		break;
	}


}

void Stage::Draw() const
{

}
