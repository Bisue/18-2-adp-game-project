#pragma once
#include "Gun.h"

namespace jm
{
	class DefaultGun : public Gun
	{
	public:
		DefaultGun(const vec2& playerPos)
			: Gun(playerPos, Delay(0.35f), 35.0f, 3.0f)
		{

		}

		void fire(const vec2& targetPos) override
		{
			SM::getInstance()->stopAndPlaySound("defaultGunShoot");

			Bullet bullet(firePoint, bulletDamage, bulletSpeed, Colors::defaultGun);
			bullet.updateVelocityTo(targetPos);

			OM::getInstance()->addBullet(bullet);
		}
	};
}