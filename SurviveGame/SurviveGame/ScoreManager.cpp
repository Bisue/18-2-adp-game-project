#include "ScoreManager.h"

namespace jm
{
	ScoreManager* ScoreManager::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new ScoreManager();
		}
		return instance;
	}

	int ScoreManager::getScore()
	{
		return score;
	}
	void ScoreManager::setScore(const int& newScore)
	{
		score = newScore;
	}
	void ScoreManager::addScore(const int& point)
	{
		score += point;
	}
	int ScoreManager::getKill()
	{
		return kill;
	}
	void ScoreManager::setKill(const int& newKill)
	{
		kill = newKill;
	}
	void ScoreManager::addKill(const int& kill)
	{
		this->kill += kill;
	}

	void ScoreManager::reset()
	{
		score = 0;
		kill = 0;
	}

	ScoreManager* ScoreManager::instance = nullptr;
}