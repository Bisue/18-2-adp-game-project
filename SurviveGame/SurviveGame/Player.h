#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include <vector>
#include "SoundManager.h"
#include "Delay.h"
#include "ObjectManager.h"

namespace jm
{
	class Player : public GameObject
	{
		using SM = SoundManager;
	private:
		Delay fireDelay = Delay(0.2f);

		float speed;
		int powerLevel = 1;

	public:
		//constructor
		Player(const vec2& position, const float& speed)
			: GameObject(position, 0.05f), speed(speed)
		{ }
		//getter, setter
		float getSpeed() const
		{
			return speed;
		}
		void setSpeed(const float& speed)
		{
			this->speed = speed;
		}
		void increasePower()
		{
			powerLevel++;
		}

		//methods
		void shoot(const vec2& targetPos) 
		{
			if(fireDelay.check())
			{
				SM::getInstance()->stopAndPlaySound("playerShoot");

				Bullet bullet(position, powerLevel*40.0f, 4.0f);
				bullet.updateVelocityTo(targetPos);

				OM::getInstance()->addBullet(bullet);
			}
		}
		void move(vec2 dirVector)
		{
			position += dirVector* speed * DELTATIME;
		}
		void lookAt(vec2 mousePos)
		{
			vec2 diff = mousePos - position;
			float rad = diff.getRad();
			rotation = getDegree(rad);
		}
		void render() const override
		{
			beginTransformation();
			{
				translate(position);
				rotate(rotation);
				//body
				beginTransformation();
				{
					drawFilledTriangle(Colors::blue, vec2(0.1f, 0.0f), vec2(-0.05f, 0.02f), vec2(-0.05f, -0.02f));
				}
				endTransformation();
				//충돌반경(디버그용)
				beginTransformation();
				{
					drawWiredCircle(Colors::black, bodyRadius);
				}
				endTransformation();
			}
			endTransformation();
		}
	};
}