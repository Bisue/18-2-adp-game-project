#pragma once
#include "DrawFunctions.h"
#include <random>

namespace jm
{
	//TODO: think that Singleton Pattern is required
	class Randomization
	{
	private:
		static Randomization* instance;
		static std::mt19937 mer;

		Randomization()
		{
		}
		Randomization(const Randomization& other)
		{
		}

	public:
		static Randomization* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new Randomization();
				std::random_device rd;
				instance->mer = std::mt19937(rd());
			}
			return instance;
		}

		float randomFloat(float min, float max);
		int randomInt(int min, int max);
		vec2 randomDirVector(); // �������⺤�͸� ��ȯ (����: �� ���⺤�Ͱ� ���� Ȯ���� �������� ����..(�簢������ ��ǥ�� ��))
	};
	using RD = Randomization;
}