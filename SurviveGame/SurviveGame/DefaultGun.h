#pragma once
#include "Gun.h"

namespace jm
{
	class DefaultGun : public Gun
	{
	private:

	public:
		DefaultGun(const vec2& playerPos)
			: Gun(playerPos, Delay(0.2f), 40.0f, 4.0f)
		{

		}

		void fire(const vec2& targetPos) override
		{
			SM::getInstance()->stopAndPlaySound("playerShoot");

			Bullet bullet(firePoint, bulletDamage, 4.0f);
			bullet.updateVelocityTo(targetPos);

			OM::getInstance()->addBullet(bullet);
		}
	};
}