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
		Monster(const vec2& position, const float& speed, const float& bodyRadius, const float& maxHp, const Delay& calDirDelay, const float& recogRad = 0.35f);

		//이동관련
		void moveTo(const vec2& targetPos);
		void updateDir(const vec2& targetPos);
		void move();

		//피해입음
		void hit(const float& damage);
		//죽었는지 확인
		bool checkDie();
		//render
		void render() const override;
		void drawHp() const;
		//pure virtual methods
		virtual void drawBody() const = 0;
		virtual RGB getColor() const = 0;
	};
}