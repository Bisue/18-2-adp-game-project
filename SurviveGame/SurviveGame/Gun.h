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
		vec2 firePoint; //총알 발사위치
		Delay fireDelay; //발사 딜레이
		float bulletDamage;
		float bulletSpeed;
		
		//int maxBullets; //탄창 최대치
		//int curBullets; //탄창 잔량
		//Delay reloadDelay; //장전 딜레이

	public:
		//생성자
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

		//void reload() //장전
		//{
		//	...
		//}

		//순수가상함수
		virtual void fire(const vec2& targetPos) = 0; //총알 발사
	};
}