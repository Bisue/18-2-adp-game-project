#pragma once
#include "GameObject.h"

namespace jm
{
	class Item : public GameObject
	{
	private:
		RGB color;

		float rotateTimer = 0.0f;

	public:
		Item(const vec2 position, const float radius = 0.1f)
			: GameObject(position, radius), color(255, 102, 0)
		{

		}

		void update(const float& timeStep)
		{
			rotateTimer = timeStep;
		}

		void render() const override
		{
			beginTransformation();
			{
				translate(position);
				rotate(rotateTimer*60.0f);
				drawFilledPentagon(color, bodyRadius);
			}
			endTransformation();
		}
	};
}