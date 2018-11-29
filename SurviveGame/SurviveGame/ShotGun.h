#pragma once
#include "Gun.h"
#include "Randomization.h"

namespace jm
{
	class ShotGun : public Gun
	{
	public:
		ShotGun(const vec2& playerPos)
			: Gun(playerPos, Delay(0.8f), 30.0f, 5.0f)
		{

		}

		void fire(const vec2& targetPos) override
		{
			SM::getInstance()->stopAndPlaySound("playerShoot");

			Bullet bullets[5];
			for (int i = 0; i < 5; i++)
			{
				bullets[i] = Bullet(firePoint, bulletDamage, 4.0f);
				bullets[i].updateVelocityTo(targetPos + RD::getInstance()->randomDirVector()*0.1f);
				OM::getInstance()->addBullet(bullets[i]);
			}
		}
	};
}