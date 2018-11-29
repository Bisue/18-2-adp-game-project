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

		int dirFlag = 1;

	public:
		Monster(const vec2& position, const float& speed, const float& bodyRadius, const float& maxHp, const Delay& calDirDelay, const float& recogRad = 0.35f)
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
				calDirDelay.setDelay(0.05f);
				updateDir(targetPos);
			}
			else
			{
				calDirDelay.setDelay(originDelay);
				if (dirFlag == 0)
				{
					//중심이 (0,0), 반지름이 1.0f인 원 안에서 랜덤하게 움직임.
					updateDir(RD::getInstance()->randomDirVector());
				}
				else if (dirFlag == 1)
				{
					//...
					updateDir(RD::getInstance()->randomDirVector());
				}
				else
				{
					updateDir(position); //정지
				}
			}
			move();
		}
		void updateDir(const vec2& targetPos)
		{
			if (calDirDelay.check())
			{
				vec2 diff = targetPos - position;;
				moveDir = diff.nomalized();

				//rotate
				rotation = getDegree(diff.getRad());

				//flag update
				dirFlag = Randomization::getInstance()->randomInt(0, 2);
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
				//==debug
				drawWiredCircle(Colors::gray, recogRad);
				//=======
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
		//virtual methods
		virtual void drawBody() const
		{
			std::cout << "mom's draw" << std::endl;
		}
	};
}