#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include <vector>
#include "SoundManager.h"
#include "Delay.h"

namespace jm
{
	class Player : public GameObject
	{
		using SM = SoundManager;
	private:
		Delay fireDelay = Delay(0.06f);

		float speed;
		int powerLevel = 1;

	public:
		//constructor
		Player(const vec2& position, const float& speed)
			: GameObject(position, 0.05f), speed(speed)
		{
			SM::getInstance()->initSound("shoot.wav", "playerShoot", false);
		}
		//getter, setter
		float getSpeed()
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
		void shoot(std::vector<Bullet*>& bullets, const vec2& targetPos)
		{
			if(fireDelay.check())
			{
				SM::getInstance()->stopAndPlaySound("playerShoot");

				Bullet* bullet = new Bullet(position, powerLevel);
				bullet->updateVelocityTo(targetPos);

				bullets.push_back(bullet);
			}
		}
		void move(vec2 dirVector)
		{
			position += dirVector* speed * DELTATIME;
		}
		void lookAt(vec2 mousePos)
		{
			vec2 diff = mousePos - position;
			float rad = atan2(diff.y, diff.x);
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