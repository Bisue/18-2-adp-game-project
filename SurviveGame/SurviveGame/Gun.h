#pragma once
#include "Game2D.h"
#include "Delay.h"

namespace jm
{
	class Gun
	{
	private:
		vec2 firePoint; //총알 발사위치
		Delay fireDelay; //발사 딜레이
		
		//int maxBullets; //탄창 최대치
		//int curBullets; //탄창 잔량
		//Delay reloadDelay; //장전 딜레이

	public:
		//생성자
		Gun(const vec2& firePoint, const Delay& fireDelay)
			: firePoint(firePoint), fireDelay(fireDelay)
		{ }

		//void reload() //장전
		//{
		//	...
		//}

		//순수가상함수
		virtual void fire(const vec2& targetPos) = 0; //총알 발사
	};
}