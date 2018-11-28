#pragma once
#include "Game2D.h"
#include "Delay.h"

namespace jm
{
	class Gun
	{
	private:
		vec2 firePoint; //�Ѿ� �߻���ġ
		Delay fireDelay; //�߻� ������
		
		//int maxBullets; //źâ �ִ�ġ
		//int curBullets; //źâ �ܷ�
		//Delay reloadDelay; //���� ������

	public:
		//������
		Gun(const vec2& firePoint, const Delay& fireDelay)
			: firePoint(firePoint), fireDelay(fireDelay)
		{ }

		//void reload() //����
		//{
		//	...
		//}

		//���������Լ�
		virtual void fire(const vec2& targetPos) = 0; //�Ѿ� �߻�
	};
}