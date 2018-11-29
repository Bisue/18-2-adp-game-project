#pragma once
#include "GameObject.h"
#include "GameTime.h"

namespace jm
{
	class Bullet : public GameObject
	{
	private:
		vec2 dir;
		RGB color;
		float speed;
		float damage;

	public:
		Bullet(const vec2& position, const float& damage = 1, const float speed = 5.0f, const RGB& color = Colors::red)
			: GameObject(position, 0.01f), damage(damage), dir(vec2(0,0)), speed(speed), color(color)
		{ }
		float getDamage() const
		{
			return damage;
		}

		void updateVelocityTo(const vec2& targetPos)
		{
			vec2 diff = targetPos - position;
			diff /= sqrt(diff.x*diff.x + diff.y*diff.y);
			dir = diff;
		}
		void update()
		{
			position += dir * speed * DELTATIME;
		}
		void render() const override
		{
			beginTransformation();
			{
				translate(position);
				drawFilledCircle(color, bodyRadius);
			}
			endTransformation();
		}
	};
}