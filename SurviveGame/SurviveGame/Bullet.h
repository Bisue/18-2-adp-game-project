#pragma once
#include "GameObject.h"
#include "GameTime.h"

namespace jm
{
	class Bullet : public GameObject
	{
	private:
		vec2 dir;
		float speed;
		float damage;

	public:
		Bullet(const vec2& position, const int& power = 1, const vec2& dir = vec2(0.0f, 0.0f), const float speed = 5.0f)
			: GameObject(position, 0.01f), dir(dir), speed(speed)
		{
			damage = power * 15.0f;
		}
		float getDamage()
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
				drawFilledCircle(Colors::red, bodyRadius);
			}
			endTransformation();
		}
	};
}