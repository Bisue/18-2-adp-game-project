#pragma once
#include "Gun.h"
#include "Randomization.h"

namespace jm
{
	class SmgGun : public Gun
	{
	public:
		SmgGun(const vec2& playerPos)
			: Gun(playerPos, Delay(0.05f), 15.0f, 3.0f)
		{

		}

		void fire(const vec2& targetPos) override
		{
			SM::getInstance()->stopAndPlaySound("smgGunShoot");

			Bullet bullet(firePoint, bulletDamage, bulletSpeed);

			//·£´ýÈ­
			vec2 fpToTp = targetPos - firePoint;
			float deg = getDegree(fpToTp.getRad());
			deg += Randomization::getInstance()->randomFloat(-5.0f, 5.0f);
			float rad = getRadian(deg);
			vec2 newTargetPos(targetPos.getMagnitude()*std::cosf(rad), targetPos.getMagnitude()*std::sinf(rad));
			newTargetPos += firePoint;

			bullet.updateVelocityTo(newTargetPos);
			OM::getInstance()->addBullet(bullet);
		}
	};
}
