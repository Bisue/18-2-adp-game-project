#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include <memory>
#include <vector>
#include "SoundManager.h"
#include "Delay.h"
#include "ObjectManager.h"
#include "ShotGun.h"
#include "DefaultGun.h"

namespace jm
{
	//GunManager 클래스 필요(Gun들을 담아두고 꺼내는 용도/사용가능한 Gun여부 판단)
	class Player : public GameObject
	{
		using SM = SoundManager;
	private:
		std::shared_ptr<Gun> eqGun;

		float speed;

	public:
		//constructor
		Player(const vec2& position, const float& speed)
			: GameObject(position, 0.05f), speed(speed)
		{
			std::shared_ptr<DefaultGun> startingGun = std::make_shared<DefaultGun>(position);
			eqGun = std::static_pointer_cast<std::shared_ptr<Gun>::element_type>(startingGun);
			chaneGun(); //디버그용
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

		//methods
		void update()
		{
			eqGun->asyncPos(position);
		}
		void chaneGun() //미완(디버그용)
		{
			eqGun.reset();
			std::shared_ptr<ShotGun> useGun = std::make_shared<ShotGun>(position);
			eqGun = std::static_pointer_cast<std::shared_ptr<Gun>::element_type>(useGun);
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