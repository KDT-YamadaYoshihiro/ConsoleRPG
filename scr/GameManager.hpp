#pragma once


class GameManager
{
	GameManager()
		:m_running(true)
	{

	}

	virtual ~GameManager() = default;

public:

	GameManager(GameManager&) = delete;
	GameManager& operator=(GameManager&) = delete;

	static GameManager& Instace()
	{
		static GameManager instance;
		return  instance;
	}

	void Run();

	/// <summary>
	/// 終了フラグを折る
	/// </summary>
	void Finalize()
	{
		m_running = false;
	}

	/// <summary>
	/// リソース系はここ
	/// </summary>
	int Shutdown()
	{
		return 0;
	}

private:

	bool m_running;

};