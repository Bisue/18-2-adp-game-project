#pragma once
#include "GameObject.h"
#include "Randomization.h"
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

		float originDelay; //기본 calDirDelay 임시저장변수
		float recogRad; //플레이어 인식거리

		bool dirFlag = true;

	public:
		Monster(const vec2& position, const float& speed, const float& bodyRadius, const float& maxHp, const Delay& calDirDelay, const float& recogRad = 0.5f)
			: GameObject(position, bodyRadius), calDirDelay(calDirDelay), speed(speed), maxHp(maxHp), curHp(maxHp), recogRad(recogRad)
		{
			moveDir = vec2(0, 0);
			originDelay = calDirDelay.getDelay();
		}

		//move
		void moveTo(const vec2& targetPos)
		{
			if ((targetPos - position).getMagnitude() < recogRad)
			{
				calDirDelay.setDelay(0.1f);
				updateDir(targetPos);
			}
			else
			{
				calDirDelay.setDelay(originDelay);
				if (dirFlag)
				{
					updateDir(RD::getInstance()->randomDirVector());
					dirFlag = !dirFlag;
				}
				else
				{
					updateDir(targetPos);
					dirFlag = !dirFlag;
				}
			}
			move();
		}
		void updateDir(const vec2& targetPos)
		{
			if (calDirDelay.check())
			{
				vec2 diff = targetPos - position;
				diff /= sqrt(diff.x*diff.x + diff.y*diff.y);
				moveDir = diff;

				//rotate
				rotation = getDegree(diff.getRad());
			}
		}
		void move()
		{
			vec2 velocity = moveDir * speed;
			position += velocity * DELTATIME;
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
			beginTransformation();
			{
				translate(position);
				rotate(rotation);
				drawBody();
			}
			endTransformation();
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