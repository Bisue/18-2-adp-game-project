#pragma once

namespace jm
{
	//singleton
	class ScoreManager
	{
	private:
		static ScoreManager* instance;

		int score = 0; //����
		int kill = 0;  //ų ��

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

		//����, ų �� �ʱ�ȭ
		void reset();
	};
	using SCM = ScoreManager;
}