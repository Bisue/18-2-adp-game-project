#pragma once

namespace jm
{
	//singleton
	class ScoreManager
	{
	private:
		static ScoreManager* instance;

		int score = 0; //점수
		int kill = 0;  //킬 수

		ScoreManager()
		{ }
		ScoreManager(const ScoreManager& other)
		{ }

	public:
		static ScoreManager* getInstance();

		//getter, setter, adder
		int getScore();
		void setScore(const int& newScore);
		void addScore(const int& point);
		int getKill();
		void setKill(const int& newKill);
		void addKill(const int& kill);

		//점수, 킬 수 초기화
		void reset();
	};
	using SCM = ScoreManager;
}