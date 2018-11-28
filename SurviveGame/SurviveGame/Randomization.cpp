#include "Randomization.h"

namespace jm
{
	float Randomization::randomFloat(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(mer);
	}
	int Randomization::randomInt(int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mer);
	}
	vec2 Randomization::randomDirVector()
	{
		// 사각형안의 랜덤좌표를 받음
		vec2 temp(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f));
		return temp.nomalized(); // nomalize한 뒤 반환
	}

	Randomization* Randomization::instance = nullptr;
	std::mt19937 Randomization::mer = instance->mer = std::mt19937(std::random_device()());
}