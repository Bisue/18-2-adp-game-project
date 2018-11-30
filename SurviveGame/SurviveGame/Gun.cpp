#include "Gun.h"

namespace jm
{
	Gun::Gun(const vec2& playerPos, const Delay& fireDelay, const float& bulletDamage, const float& bulletSpeed)
		: firePoint(playerPos), fireDelay(fireDelay), bulletDamage(bulletDamage), bulletSpeed(bulletSpeed)
	{
	}

	vec2 Gun::getFirePoint() const
	{
		return firePoint;
	}
	void Gun::setFirePoint(const vec2& newPoint)
	{
		firePoint = newPoint;
	}

	void Gun::asyncPos(const vec2& playerPos)
	{
		firePoint = playerPos;
	}

	void Gun::shoot(const vec2& targetPos)
	{
		if (fireDelay.check())
		{
			fire(targetPos);
		}
	}
}