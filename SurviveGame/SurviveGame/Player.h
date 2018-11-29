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
	//GunManager Ŭ���� �ʿ�(Gun���� ��Ƶΰ� ������ �뵵/��밡���� Gun���� �Ǵ�)
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
			chaneGun(); //����׿�
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
		void chaneGun() //�̿�(����׿�)
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
				//�浹�ݰ�(����׿�)
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