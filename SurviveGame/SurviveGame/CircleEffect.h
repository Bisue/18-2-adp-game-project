#pragma once
#include <Delay.h>
#include <GameObject.h>
#include <GameTime.h>

namespace jm
{
	class CircleEffect : public GameObject
	{
	private:
		RGB color;
		Delay lifeTime;
		float curTime;
		float circleSize;
		float maxSize;

	public:
		CircleEffect(const vec2& pos, const float& maxSize = 0.2f, const RGB& color = Colors::gray, const float& life = 0.3f)
			: GameObject(pos, 0.0f), color(color), lifeTime(life)
		{
			curTime = 0.0f;
			circleSize = 0.0f;
			this->maxSize = Randomization::getInstance()->randomFloat(0.8f, 1.2f)*maxSize;
		}

		float sizeFunc(float time)
		{
			float curX = time / lifeTime.getDelay();
			float curY = -((curX - 1)*(curX - 1)) + 1;
			return curY * maxSize;
		}

		void update()
		{
			curTime += DELTATIME;
			circleSize = sizeFunc(curTime);
		}

		bool checkLife()
		{
			return lifeTime.check();
		}

		void render() const override
		{
			beginTransformation();
			translate(position);
			setLineWidth(6.0f);
			drawWiredCircle(color, circleSize);
			setLineWidth(1.0f);
			endTransformation();
		}
	};
}