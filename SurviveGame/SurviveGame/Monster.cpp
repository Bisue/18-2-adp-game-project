#include "Monster.h"
#include "Constants.h"

namespace jm
{
	Monster::Monster(const vec2& position, const float& speed, const float& bodyRadius, const float& maxHp, const Delay& calDirDelay, const float& recogRad)
		: GameObject(position, bodyRadius), calDirDelay(calDirDelay), speed(speed), maxHp(maxHp), curHp(maxHp), recogRad(recogRad)
	{
		moveDir = vec2(0, 0);
		originDelay = calDirDelay.getDelay();
	}

	void Monster::moveTo(const vec2& targetPos)
	{
		if ((targetPos - position).getMagnitude() < recogRad)
		{
			calDirDelay.setDelay(0.05f);
			updateDir(targetPos);
		}
		else
		{
			calDirDelay.setDelay(originDelay);
			if (dirFlag == 0 || dirFlag == 1)
			{
				//�߽��� (0,0), �������� SCREENBORDER�� �� �ȿ��� �����ϰ� ������.
				updateDir(RD::getInstance()->randomDirVector()*SCREENBORDER);
			}
			else
			{
				updateDir(position); //����
			}
		}
		move();
	}
	void Monster::updateDir(const vec2& targetPos)
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
	void Monster::move()
	{
		vec2 velocity = moveDir * speed;
		position += velocity * DELTATIME;
	}
	void Monster::hit(const float& damage)
	{
		curHp -= damage;
	}
	bool Monster::checkDie()
	{
		return curHp <= 0;
	}

	void Monster::render() const
	{
		beginTransformation();
		{
			translate(position);
			rotate(rotation);
			//==debug
			//drawWiredCircle(Colors::gray, recogRad);
			//=======
			drawBody();
		}
		endTransformation();
		drawHp();
	}
	void Monster::drawHp() const
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
}