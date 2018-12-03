#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include <memory>
#include <vector>
#include "SoundManager.h"
#include "Delay.h"
#include "ObjectManager.h"
#include "SmgGun.h"
#include "ShotGun.h"
#include "DefaultGun.h"

namespace jm
{
	//GunManager 클래스 필요(Gun들을 담아두고 꺼내는 용도/사용가능한 Gun여부 판단)
	class Player : public GameObject
	{
		using SM = SoundManager;
	private:
		RGB gunColor;

		std::shared_ptr<Gun> eqGun;
		bool eqableGun[3] = { true,false,false };
		int nextUnlockGunNum = 2;

		float speed;

	public:
		//constructor
		Player(const vec2& position, const float& speed)
			: GameObject(position, 0.05f), speed(speed)
		{
			changeGun(1);
		}
		//getter, setter
		float getSpeed() const
		{
			return speed;
		}
		void setSpeed(const float& speed)
		{
			this->speed = speed;
		}
		void setColor(const RGB& color)
		{
			gunColor = color;
		}
		int getNextUnlockGunNum()
		{
			return nextUnlockGunNum;
		}

		//methods
		void update()
		{
			eqGun->asyncPos(position);
		}
		void changeGun(int gunNum)
		{
			int gunIdx = gunNum - 1;
			switch (gunNum)
			{
			case 1:
				if (eqableGun[gunIdx])
				{
					eqGun.reset();
					eqGun = std::static_pointer_cast<std::shared_ptr<Gun>::element_type>(std::make_shared<DefaultGun>(position));
					setColor(Colors::blue);
				}
				break;
			case 2:
				if (eqableGun[gunIdx])
				{
					eqGun.reset();
					eqGun = std::static_pointer_cast<std::shared_ptr<Gun>::element_type>(std::make_shared<ShotGun>(position));
					setColor(Colors::hotpink);
				}
				break;
			case 3:
				if (eqableGun[gunIdx])
				{
					eqGun.reset();
					eqGun = std::static_pointer_cast<std::shared_ptr<Gun>::element_type>(std::make_shared<SmgGun>(position));
					setColor(Colors::gold);
				}
				break;
			default:
				break;
			}
		}
		void enableGun()
		{
			if (nextUnlockGunNum > 3)
				return;
			eqableGun[nextUnlockGunNum-1] = true;
			nextUnlockGunNum++;
		}
		void shoot(const vec2& targetPos) 
		{
			eqGun->shoot(targetPos);
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
				//베이스
				beginTransformation();
				{
					drawFilledCircle(Colors::black, bodyRadius);
				}
				endTransformation();
				//무기관련
				beginTransformation();
				{
					drawFilledTriangle(gunColor, vec2(0.1f, 0.0f), vec2(-0.05f, 0.02f), vec2(-0.05f, -0.02f));
				}
				endTransformation();
			}
			endTransformation();
		}
	};
}