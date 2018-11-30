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
		
	public:
		//������
		Gun(const vec2& playerPos, const Delay& fireDelay, const float& bulletDamage, const float& bulletSpeed);

		vec2 getFirePoint() const;
		void setFirePoint(const vec2& newPoint);
		
		void asyncPos(const vec2& playerPos);
		
		void shoot(const vec2& targetPos);

		//���������Լ�
		virtual void fire(const vec2& targetPos) = 0; //�Ѿ� �߻�
	};
}