#pragma once
#include <random>

namespace jm
{
	class Randomization
	{
	private:
		static Randomization* instance;
		std::mt19937 mer;

		Randomization()
		{ }
		Randomization(const Randomization& other)
		{ }

	public:
		static Randomization* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new Randomization();
			}
			return instance;
		}
		float randomFloat(float s, float e)
		{
			std::random_device rd;
			mer = std::mt19937(rd());
			std::uniform_real_distribution<float> dist(s, e);
			return dist(mer);
		}
		int randomInt(int s, int e)
		{
			std::random_device rd;
			mer = std::mt19937(rd());
			std::uniform_int_distribution<int> dist(s, e);
			return dist(mer);
		}
	};
}