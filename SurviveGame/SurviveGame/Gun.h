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
		
	public:
		//생성자
		Gun(const vec2& playerPos, const Delay& fireDelay, const float& bulletDamage, const float& bulletSpeed);

		vec2 getFirePoint() const;
		void setFirePoint(const vec2& newPoint);
		
		void asyncPos(const vec2& playerPos);
		
		void shoot(const vec2& targetPos);

		//순수가상함수
		virtual void fire(const vec2& targetPos) = 0; //총알 발사
	};
}