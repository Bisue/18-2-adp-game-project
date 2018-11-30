#pragma once
#include "Gun.h"
#include "Randomization.h"

namespace jm
{
	class ShotGun : public Gun
	{
	public:
		ShotGun(const vec2& playerPos)
			: Gun(playerPos, Delay(0.8f), 50.0f, 3.0f)
		{

		}

		void fire(const vec2& targetPos) override
		{
			SM::getInstance()->stopAndPlaySound("shotGunShoot");

			Bullet bullets[5];
			for (int i = 0; i < 5; i++)
			{
				bullets[i] = Bullet(firePoint, bulletDamage, bulletSpeed);

				//산탄도계산 -> 각 총알의 targetPos 갱신
				vec2 fpToTp = targetPos - firePoint;
				float deg = getDegree(fpToTp.getRad());
				deg += -10.0f + 5.0f*i;
				float rad = getRadian(deg);
				vec2 newTargetPos(targetPos.getMagnitude()*std::cosf(rad), targetPos.getMagnitude()*std::sinf(rad));
				newTargetPos += firePoint;

				bullets[i].updateVelocityTo(newTargetPos);
				OM::getInstance()->addBullet(bullets[i]);
			}
		}
	};
}