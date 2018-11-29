#pragma once

namespace jm
{
	class ScoreManager
	{
	private:
		static ScoreManager* instance;

		int score = 0;
		int kill = 0;

		ScoreManager()
		{ }
		ScoreManager(const ScoreManager& other)
		{ }

	public:
		static ScoreManager* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new ScoreManager();
			}
			return instance;
		}

		int getScore()
		{
			return score;
		}
		void setScore(const int& newScore)
		{
			score = newScore;
		}
		int getKill()
		{
			return kill;
		}
		void setKill(const int& newKill)
		{
			kill = newKill;
		}
		void addScore(const int& point)
		{
			score += point;
		}
		void addKill(const int& kill)
		{
			this->kill += kill;
		}

		void reset()
		{
			score = 0;
		}
	};
}