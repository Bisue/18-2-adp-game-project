#pragma once
#include "GameObject.h"
#include "Delay.h"

namespace jm
{
	class Monster : public GameObject
	{
	protected:
		Delay calDirDelay;

		vec2 moveDir;
		float speed;
		float maxHp;
		float curHp;


	public:
		Monster(const vec2& position, const float& speed, const float& bodyRadius, const float& maxHp, const Delay& calDirDelay)
			: GameObject(position, bodyRadius), calDirDelay(calDirDelay), speed(speed), maxHp(maxHp), curHp(maxHp)
		{
			moveDir = vec2(0, 0);
		}

		//move
		void moveTo(const vec2& targetPos)
		{
			updateDir(targetPos);
			move();
		}
		void updateDir(const vec2& targetPos)
		{
			if (calDirDelay.check())
			{
				vec2 diff = targetPos - position;
				diff /= sqrt(diff.x*diff.x + diff.y*diff.y);
				moveDir = diff;
			}
		}
		void move()
		{
			vec2 velocity = moveDir * speed;
			position += velocity * GameTime::getInstance()->getDeltaTime();
		}

		//hit
		void hit(const float& damage)
		{
			curHp -= damage;
		}
		//checkDie
		bool checkDie()
		{
			return curHp <= 0;
		}
		//render
		void render() const override
		{
			drawBody();
			drawHp();
		}
		void drawHp() const
		{
			float hpHeight = 0.025f;
			float rate = float(curHp) / float(maxHp);
			beginTransformation();
			{
				translate(position);
				translate(0.0f, bodyRadius + hpHeight);
				drawFilledBox(Colors::black, bodyRadius * 2, hpHeight);
				translate(-bodyRadius, 0.0f);
				translate(bodyRadius*rate, 0.0f);
				drawFilledBox(Colors::red, bodyRadius*rate * 2, hpHeight);
			}
			endTransformation();
		}
		//pure virtual methods
		virtual void drawBody() const = 0;
	};
}