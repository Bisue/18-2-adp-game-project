#pragma once
#include "Game2D.h"
#include "Delay.h"
#include "Bullet.h"
#include "SoundManager.h"
#include "ObjectManager.h"

namespace jm
{
	class Gun
	{
	protected:
		vec2 firePoint; //�Ѿ� �߻���ġ
		Delay fireDelay; //�߻� ������
		float bulletDamage;
		float bulletSpeed;
		
		//int maxBullets; //źâ �ִ�ġ
		//int curBullets; //źâ �ܷ�
		//Delay reloadDelay; //���� ������

	public:
		//������
		Gun(const vec2& playerPos, const Delay& fireDelay, const float& bulletDamage, const float& bulletSpeed)
			: firePoint(playerPos), fireDelay(fireDelay), bulletSpeed(bulletSpeed)
		{ }

		vec2 getFirePoint() const
		{
			return firePoint;
		}
		void setFirePoint(const vec2& newPoint)
		{
			firePoint = newPoint;
		}
		
		void asyncPos(const vec2& playerPos)
		{
			firePoint = playerPos;
		}
		
		void shoot(const vec2& targetPos)
		{
			if (fireDelay.check())
			{
				fire(targetPos);
			}
		}

		//void reload() //����
		//{
		//	...
		//}

		//���������Լ�
		virtual void fire(const vec2& targetPos) = 0; //�Ѿ� �߻�
	};
}